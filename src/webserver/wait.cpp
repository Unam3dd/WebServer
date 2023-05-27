/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:10:21 by ldournoi          #+#    #+#             */
/*   Updated: 2023/05/27 04:36:55 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_request.hpp"
#include "http_server.hpp"
#include "http_status.hpp"
#include "http_utils.hpp"
#include "http_colors.hpp"
#include "http_response.hpp"
#include "webserver.hpp"
#include "utils.hpp"
#include <asm-generic/ioctls.h>
#include <cstdio>
#include <new>
#include <signals.hpp>
#include <streambuf>
#include <sys/epoll.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <sys/ioctl.h>
#include <sys/timerfd.h>
#include <string>

t_status	WebServer::_acceptClient(ev_t *e)
{
	Socket	*client = NULL;
	ev_t	tev;
	int		tfd = 0;

	if (!e) return (STATUS_FAIL);

	struct itimerspec its;
	its.it_value.tv_sec = 10;
	its.it_value.tv_nsec = 0;
	its.it_interval.tv_sec = 0;
	its.it_interval.tv_nsec = 0;

	FOREACH_VECTOR(HttpServer*, this->_srv, srv)
	{
		if (e->data.fd == (*srv)->getSocket().Getfd())
		{
			client = (*srv)->getSocket().Accept();
			if (client) 
			{
				client->SetSrvPort((*srv)->getPort());
				(*srv)->getClients().push_back(client);

				tev.data.ptr = client;
				tev.events = EPOLLIN;
				fcntl(client->Getfd(), F_SETFL, fcntl(client->Getfd(), F_GETFL, 0) | O_NONBLOCK);
				this->_epoll.Ctl(EPOLL_CTL_ADD, client->Getfd(), &tev);

				tfd = timerfd_create(CLOCK_MONOTONIC, 0);
				timerfd_settime(tfd, 0, &its, NULL);
				this->_timerfds.insert(std::pair<int, int>(client->Getfd(), tfd));
				tev.events = EPOLLIN | EPOLLET;
				tev.data.fd = tfd;
				this->_epoll.Ctl(EPOLL_CTL_ADD, tfd, &tev);
				client->SetTfd(tfd);

				_clients.push_back(client);
				std::cout << SUCCESS << "[WebServer::Wait] New client Accepted ! " << client->InetNtoa(client->GetSin()->sin_addr.s_addr) << ":" << client->Ntohs(client->GetSin()->sin_port) << std::endl;
				return (STATUS_OK);
			}
		}
	}

	return (STATUS_FAIL);
}

t_status	WebServer::_waitSrvs(void)
{
	std::string	bufs[MAX_EVENT];
	char		*tmpbufs[MAX_EVENT] = {NULL};

	size_t	size = 0;
	epoll_event evs[MAX_EVENT];
	int	nfds = 0;
	int i = 0;
	int sock_fd = 0;
	int bufindex = 0;

	Socket* client = NULL;

	// TODO: Setup Signals
	sig_setup();
	this->_run = 1;

	while (_run)
	{
		nfds = _epoll.Wait(evs, MAX_EVENT, -1);

		for (i = 0; i < nfds; i++) {

			if (_acceptClient(&evs[i]) == STATUS_OK)
				continue;
			
			client = this->_getClientSocketFromEvent(&evs[i]);
			if (!client)
			{
				logz.log(2, "cannot find client socket from event");
				continue;
			}
			sock_fd = client->Getfd();
			bufindex = sock_fd % MAX_EVENT;

			if (evs[i].events & EPOLLIN) {
				if ((unsigned long long)evs[i].data.fd < lowest_heap_address()) { //black magic: epoll_event.data is union, so if we store an fd instead on a ptr, it will always be inferior to a memory address
					logz.log(1, "EPOLLIN : timerfd. Sending timeout response.");
					::read(evs[i].data.fd, &size, sizeof(size));
					this->_respondAndClean(HTTP_STATUS_REQUEST_TIMEOUT, client->Getfd());
					bufs[bufindex].clear();
					continue;
				}

				::ioctl(sock_fd, FIONREAD, &size);
				if (!size) continue;

				logz.log(1, "EPOLLIN : size of packet: " + NumberToString(size));
				tmpbufs[bufindex] = new char[size + 1];

				if (!tmpbufs[bufindex]) {
					logz.log(2, "Bad Alloc");
					delete[] tmpbufs[bufindex];
					tmpbufs[bufindex] = NULL;
					continue ;
				}

				if (::read(sock_fd, tmpbufs[bufindex], size) != (int)size)
				{
					logz.log(2, "Read error");
					continue ;
				}

				bufs[bufindex].reserve(size);
				for (size_t j = 0; j < size; j++) {
					bufs[bufindex].push_back(tmpbufs[bufindex][j]);
				}
				logz.log(1, "EPOLLIN : request size now of: " + NumberToString(bufs[bufindex].size()));

				delete[] tmpbufs[bufindex];
				tmpbufs[bufindex] = NULL;

				//we reset the timerfd
				logz.log(1, "EPOLLIN : Resetting timerfd");
				struct itimerspec new_value;
				new_value.it_value.tv_sec = 10;
				new_value.it_value.tv_nsec = 0;
				new_value.it_interval.tv_sec = 0;
				new_value.it_interval.tv_nsec = 0;
				timerfd_settime(this->_timerfds[sock_fd], 0, &new_value, NULL);

				//we check for end of header, then check if it is a POST, and then check for content-length received
				if (!(evs[i].events & EPOLLOUT) && (bufs[bufindex].find("\r\n\r\n") != std::string::npos || bufs[bufindex].find("\n\n") != std::string::npos))
				{
					if (bufs[bufindex].substr(0, 4) == "POST")
					{
						logz.log(1, "EPOLLIN : Found end of header (\\r\\n\\r\\n), but method POST. Searching content-length...");
						if (bufs[bufindex].find("Content-Length: ") > bufs[bufindex].find("\r\n\r\n")
						&&  bufs[bufindex].find("content-length: ") > bufs[bufindex].find("\r\n\r\n"))
						{
							logz.log(1, "EPOLLIN : No content-length found. Returning 411");
							this->_respondAndClean(HTTP_STATUS_LENGTH_REQUIRED, sock_fd);
							bufs[bufindex].clear();
							continue;
						}
						else
						{
							logz.log(1, "EPOLLIN : Content-length found. parsing value...");
							size_t pos = bufs[bufindex].find("Content-Length:");
							if (pos == std::string::npos)
								pos = bufs[bufindex].find("content-length:");
							size_t pos2 = bufs[bufindex].find("\r\n", pos);
							std::string content_length = bufs[bufindex].substr(pos + 15, pos2 - pos - 15);
							logz.log(1, "EPOLLIN : Content-length parsed. Content-length: " + content_length);
							if (StringToNumber<unsigned long>(content_length) > bufs[bufindex].size() - bufs[bufindex].find("\r\n\r\n") - 4)
							{
								logz.log(1, "EPOLLIN : Content-length is bigger than what we have. Keeping EPOLLIN and rolling again!");
								continue;
							} else
							{
								logz.log(1, "EPOLLIN : We have content-length bytes. Setting EPOLLOUT.");
								evs[i].events = EPOLLIN | EPOLLOUT;
								this->_epoll.Ctl(EPOLL_CTL_MOD, sock_fd, &evs[i]);
								continue ;
							}
						}
					}
					logz.log(1, "EPOLLIN : Found end of header (\\r\\n\\r\\n). Setting EPOLLOUT. If there's data to be read, it should be read before going to EPOLLOUT");
					evs[i].events = EPOLLIN | EPOLLOUT;
					this->_epoll.Ctl(EPOLL_CTL_MOD, sock_fd, &evs[i]);
				}
			}
			else if (evs[i].events & EPOLLOUT) {
				HttpRequest req(bufs[bufindex], static_cast<Socket*>(evs[i].data.ptr)->GetSrvPort(), const_cast<char*>(static_cast<Socket*>(evs[i].data.ptr)->InetNtoa(static_cast<Socket*>(evs[i].data.ptr)->GetSin()->sin_addr.s_addr).c_str()));
				#if DEBUG
					std::cout << DBG << "[WebServer::Wait] Parsed request: " << std::endl << req << std::endl;
				#endif

				HttpResponse res(req);
				#if DEBUG
					std::cout << DBG << "[WebServer::Wait] Generated response, status code: " << res.getStatusCodeStr() << std::endl;
				#endif
				write(static_cast<Socket*>(evs[i].data.ptr)->Getfd(), res.getResponse().c_str(), res.getResponse().size());

				::close(static_cast<Socket*>(evs[i].data.ptr)->Getfd());
				_epoll.Ctl(EPOLL_CTL_DEL, static_cast<Socket*>(evs[i].data.ptr)->Getfd(), NULL);
				#if DEBUG
					std::cout << DBG << "[WebServer::_wait] _clients.size(): " << _clients.size() << std::endl;
				#endif
				FOREACH_VECTOR(Socket*, _clients, it){
					if (*it == evs[i].data.ptr) _clients.erase(it);
				}
				::close(static_cast<Socket*>(evs[i].data.ptr)->GetTfd());
				_epoll.Ctl(EPOLL_CTL_DEL, static_cast<Socket*>(evs[i].data.ptr)->GetTfd(), NULL);
				this->_timerfds.erase(static_cast<Socket*>(evs[i].data.ptr)->Getfd());
				delete static_cast<Socket*>(evs[i].data.ptr);
				bufs[bufindex].clear();
				#if DEBUG
					std::cout << DBG << "[WebServer::_wait] response sent and cleanup done." << std::endl;
				#endif
			}

		}
	}

	FOREACH_VECTOR(Socket*, this->_clients, it){ delete *it; }
	for (int i = 0; i < MAX_EVENT; i++)
		if (tmpbufs[i]) delete tmpbufs[i];
	return (STATUS_OK);
}
