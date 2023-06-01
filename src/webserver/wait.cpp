/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:10:21 by ldournoi          #+#    #+#             */
/*   Updated: 2023/06/01 10:37:05 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_request.hpp"
#include "http_server.hpp"
#include "http_status.hpp"
#include "http_utils.hpp"
#include "logger.hpp"
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

static void	resetTimerFd(unsigned int sec, unsigned int fd){
	logz.log(L_DEBUG, "EPOLLIN: Resetting timerfd");

	struct itimerspec new_value;

	new_value.it_value.tv_sec = sec;
	new_value.it_value.tv_nsec = 0;
	new_value.it_interval.tv_sec = 0;
	new_value.it_interval.tv_nsec = 0;
	
	timerfd_settime(fd, 0, &new_value, NULL);
}

t_status	WebServer::_acceptClient(ev_t *e)
{
	Socket	*client = NULL;
	ev_t	tev;
	int		tfd = 0;

	if (!e) return (STATUS_FAIL);

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
				resetTimerFd(REQUEST_TIMEOUT, tfd);
				this->_timerfds.insert(std::pair<int, int>(client->Getfd(), tfd));
				tev.events = EPOLLIN | EPOLLET;
				tev.data.fd = tfd;
				this->_epoll.Ctl(EPOLL_CTL_ADD, tfd, &tev);
				client->SetTfd(tfd);

				_clients.push_back(client);
				logz.log(L_PASS | L_BYPASS, "New client accepted ! " +
					client->InetNtoa(client->GetSin()->sin_addr.s_addr) + ":" +
					logz.itoa(client->Ntohs(client->GetSin()->sin_port)));
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
				logz.log(L_ERROR, "cannot find client socket from event");
				continue;
			}
			sock_fd = client->Getfd();
			bufindex = sock_fd % MAX_EVENT;

			if (evs[i].events & EPOLLIN) {
				if ((unsigned long long)evs[i].data.fd < lowest_heap_address()) { //black magic
					logz.log(L_DEBUG, "EPOLLIN : timerfd. Sending timeout response.");
					::read(evs[i].data.fd, &size, sizeof(size));
					this->_respondAndClean(HTTP_STATUS_REQUEST_TIMEOUT, client->Getfd());
					bufs[bufindex].clear();
					continue;
				}

				::ioctl(sock_fd, FIONREAD, &size);
				if (!size) continue;

				logz.log(L_DEBUG, "EPOLLIN : size of packet: " + NumberToString(size));
				tmpbufs[bufindex] = new char[size + 1];

				if (!tmpbufs[bufindex]) {
					logz.log(L_ERROR, "Bad Alloc");
					continue ;
				}

				if (::read(sock_fd, tmpbufs[bufindex], size) != (int)size)
				{
					logz.log(L_ERROR, "Read error");
					continue ;
				}

				bufs[bufindex].reserve(size);
				for (size_t j = 0; j < size; j++) {
					bufs[bufindex].push_back(tmpbufs[bufindex][j]);
				}
				logz.log(L_DEBUG, "EPOLLIN : request size now of: " + NumberToString(bufs[bufindex].size()));

				delete[] tmpbufs[bufindex];
				tmpbufs[bufindex] = NULL;

				//we reset the timerfd
				resetTimerFd(REQUEST_TIMEOUT, this->_timerfds[sock_fd]);

			
				//we check for end of header, then check if it is a POST, and then check for content-length received
				if (!(evs[i].events & EPOLLOUT) && (bufs[bufindex].find("\r\n\r\n") != std::string::npos || bufs[bufindex].find("\n\n") != std::string::npos))
				{
					if (bufs[bufindex].substr(0, 4) == "POST")
					{
						logz.log(L_DEBUG, "EPOLLIN : Found end of header (\\r\\n\\r\\n), but method POST. Searching content-length...");
						long long reqsize = this->_checkContentLength(bufs[bufindex]);
						if (reqsize < 0)
						{
							logz.log(L_DEBUG, "EPOLLIN : No or invalid content-length found. Returning 411");
							this->_respondAndClean(HTTP_STATUS_LENGTH_REQUIRED, sock_fd);
							bufs[bufindex].clear();
							continue;
						}
						else
						{
							if (reqsize > (long long)(bufs[bufindex].size() - bufs[bufindex].find("\r\n\r\n") - 4))
							{
								logz.log(L_DEBUG, "EPOLLIN : Content-length is bigger than what we have. Keeping EPOLLIN and rolling again!");
								continue;
							} else
							{
								logz.log(L_DEBUG, "EPOLLIN : We have content-length bytes. Setting EPOLLOUT.");
								evs[i].events = EPOLLIN | EPOLLOUT;
								this->_epoll.Ctl(EPOLL_CTL_MOD, sock_fd, &evs[i]);
								continue ;
							}
						}
					}
					logz.log(L_DEBUG, "EPOLLIN : Found end of header (\\r\\n\\r\\n). Setting EPOLLOUT.");
					logz.log(L_DEBUG, "If there's data to be read, it should be read before going to EPOLLOUT");
					evs[i].events = EPOLLIN | EPOLLOUT;
					this->_epoll.Ctl(EPOLL_CTL_MOD, sock_fd, &evs[i]);
				}
			}
			else if (evs[i].events & EPOLLOUT) {
				HttpRequest req(bufs[bufindex], client->GetSrvPort(), const_cast<char*>(client->InetNtoa(client->GetSin()->sin_addr.s_addr).c_str()));
		
				std::ostringstream oss;
				oss << req;
				logz.log(L_DEBUG, "parsed request: " + oss.str());

				HttpResponse res(req);
				
				logz.log(L_DEBUG, "EPOLLOUT : Sending response with code " + res.getStatusCodeStr());
				write(client->Getfd(), res.getResponse().c_str(), res.getResponse().size());
				::close(client->Getfd());
				_epoll.Ctl(EPOLL_CTL_DEL, client->Getfd(), NULL);
				
				FOREACH_VECTOR(Socket*, _clients, it){
					if (*it == evs[i].data.ptr) _clients.erase(it);
				}
				
				::close(client->GetTfd());
				_epoll.Ctl(EPOLL_CTL_DEL, client->GetTfd(), NULL);
				this->_timerfds.erase(client->Getfd());

				delete client;
				bufs[bufindex].clear();

				logz.log(1, "EPOLLOUT : Response sent and cleanup done.");
			}
		}
	}

	FOREACH_VECTOR(Socket*, this->_clients, it){ delete *it; }
	for (int i = 0; i < MAX_EVENT; i++)
		if (tmpbufs[i]) delete tmpbufs[i];
	return (STATUS_OK);
}
