/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:10:21 by ldournoi          #+#    #+#             */
/*   Updated: 2023/05/23 17:32:26 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_request.hpp"
#include "http_server.hpp"
#include "http_utils.hpp"
#include "http_colors.hpp"
#include "http_response.hpp"
#include "webserver.hpp"
#include <asm-generic/ioctls.h>
#include <cstdio>
#include <new>
#include <signals.hpp>
#include <streambuf>
#include <sys/epoll.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sys/ioctl.h>
#include <sys/timerfd.h>
#include <string>

static unsigned long long	lowest_heap_address(void)
{
	std::stringstream	ss;
	std::ifstream		regions("/proc/self/maps");
	std::string			line;
	std::string			addr;
	unsigned long long	ret = 0;

	while (std::getline(regions, line))
	{
		if (line.find("[heap]") != std::string::npos)
		{
			addr = line.substr(0, line.find("-"));
			ss << std::hex << addr;
			ss >> ret;
			break;
		}
	}
	if (!ret)
		return (0xFFFFFF);
	return (ret);
}

t_status	WebServer::_acceptClient(ev_t *e)
{
	Socket	*client = NULL;
	ev_t	tev;
	int		tfd = 0;

	if (!e) return (STATUS_FAIL);

	struct itimerspec its;
	its.it_value.tv_sec = 5;
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

	// TODO: Setup Signals
	sig_setup();
	this->_run = 1;

	while (_run)
	{
		nfds = _epoll.Wait(evs, MAX_EVENT, -1);

		for (i = 0; i < nfds; i++) {

			if (_acceptClient(&evs[i]) == STATUS_OK)
				continue;

			if (evs[i].events & EPOLLIN) {
				if ((unsigned long long)evs[i].data.fd < lowest_heap_address()) { //black magic: epoll_event.data is union, so if we store an fd instead on a ptr, it will always be inferior to a memory address
					if (DEBUG)
						std::cout << DBG << "[WebServer::_waitSrvs()] EPOLLIN : timerfd" << std::endl;
					::read(evs[i].data.fd, &size, sizeof(size));
					HttpResponse timeout(HTTP_STATUS_REQUEST_TIMEOUT);
					FOREACH_VECTOR(Socket*, _clients, client){
						if (evs[i].data.fd == this->_timerfds[(*client)->Getfd()]){
							::write((*client)->Getfd(), timeout.getResponse().c_str(), timeout.getResponse().size());
							::close((*client)->Getfd());
							this->_epoll.Ctl(EPOLL_CTL_DEL, (*client)->Getfd(), NULL);
							this->_timerfds.erase((*client)->Getfd());
							this->_epoll.Ctl(EPOLL_CTL_DEL, (*client)->GetTfd(), NULL);
							bufs[(*client)->Getfd() % MAX_EVENT].clear();
							break;
						}
					}
					this->_timerfds.erase(evs[i].data.fd);
					this->_epoll.Ctl(EPOLL_CTL_DEL, evs[i].data.fd, NULL);
					::close(evs[i].data.fd);
					continue;
				}

				sock_fd = static_cast<Socket*>(evs[i].data.ptr)->Getfd();
				::ioctl(sock_fd, FIONREAD, &size);
				if (!size){
					continue;
				}
				
				if (DEBUG)
					std::cout << DBG << "[WebServer::_waitSrvs()] EPOLLIN : size of packet: " << size << std::endl;

				tmpbufs[sock_fd % MAX_EVENT] = new char[size + 1];

				if (!tmpbufs[sock_fd % MAX_EVENT]) {
					std::cout << WARN << "[WebServer::_waitSrvs()] Bad Alloc" << std::endl;
					continue ;
				}

				if (::read(sock_fd, tmpbufs[sock_fd % MAX_EVENT], size) != (int)size)
				{
					if (DEBUG)
						std::cout << DBG << WARN << "[WebServer::_waitSrvs()] Read error" << std::endl;
					continue ;
				}

				bufs[sock_fd % MAX_EVENT].reserve(size + 1);
				for (size_t j = 0; j < size; j++)
					bufs[sock_fd % MAX_EVENT].push_back(tmpbufs[sock_fd % MAX_EVENT][j]);

				if (DEBUG)
				{
					std::cout << DBG << "[WebServer::_waitSrvs()] EPOLLIN : request size now of: " << bufs[sock_fd % MAX_EVENT].size() << std::endl;
					std::cout << DBG << "[WebServer::_waitSrvs()] EPOLLIN : request: " << std::endl << bufs[sock_fd % MAX_EVENT];
				}

				delete[] tmpbufs[sock_fd % MAX_EVENT];
				tmpbufs[sock_fd % MAX_EVENT] = NULL;

				if (   bufs[sock_fd % MAX_EVENT].find("\r\n\r\n") != std::string::npos
					|| bufs[sock_fd % MAX_EVENT].find("\n\n") 	  != std::string::npos) {
					if (DEBUG)
						std::cout << DBG << "[WebServer::_waitSrvs()] EPOLLIN : End of header received. Setting EPOLLOUT" << std::endl;
					evs[i].events = EPOLLOUT;
					_epoll.Ctl(EPOLL_CTL_MOD, sock_fd, &evs[i]);
				} else { //we reset the timerfd
					if (DEBUG)
						std::cout << DBG << "[WebServer::_waitSrvs()] EPOLLIN : Resetting timerfd" << std::endl;
					struct itimerspec new_value;
					new_value.it_value.tv_sec = 5;
					new_value.it_value.tv_nsec = 0;
					new_value.it_interval.tv_sec = 0;
					new_value.it_interval.tv_nsec = 0;
					timerfd_settime(this->_timerfds[sock_fd], 0, &new_value, NULL);
				}
			}
			if (evs[i].events & EPOLLOUT) {
				if (DEBUG)
					std::cout << DBG << "[WebServer::_waitSrvs()] EPOLLOUT : Sending response" << std::endl;

				HttpRequest req(bufs[sock_fd % MAX_EVENT], static_cast<Socket*>(evs[i].data.ptr)->GetSrvPort(), const_cast<char*>(static_cast<Socket*>(evs[i].data.ptr)->InetNtoa(static_cast<Socket*>(evs[i].data.ptr)->GetSin()->sin_addr.s_addr).c_str()));
				HttpResponse res(req);

				if (DEBUG)
					std::cout << DBG << "[WebServer::Wait] Received and parsed request: " << std::endl << req << std::endl;
				write(static_cast<Socket*>(evs[i].data.ptr)->Getfd(), res.getResponse().c_str(), res.getResponse().size());

				::close(static_cast<Socket*>(evs[i].data.ptr)->Getfd());
				_epoll.Ctl(EPOLL_CTL_DEL, static_cast<Socket*>(evs[i].data.ptr)->Getfd(), NULL);
				if (DEBUG)
					std::cout << DBG << "[WebServer::_wait] _clients.size(): " << _clients.size() << std::endl;
				FOREACH_VECTOR(Socket*, _clients, it){
					if (*it == evs[i].data.ptr) _clients.erase(it);
				}
				::close(static_cast<Socket*>(evs[i].data.ptr)->GetTfd());
				_epoll.Ctl(EPOLL_CTL_DEL, static_cast<Socket*>(evs[i].data.ptr)->GetTfd(), NULL);
				this->_timerfds.erase(static_cast<Socket*>(evs[i].data.ptr)->Getfd());
				delete static_cast<Socket*>(evs[i].data.ptr);
				bufs[sock_fd % MAX_EVENT].clear();
			}

			/*
			   bool datawaiting = true;
			   while (datawaiting)
			   {
			   if (tmpbuf)
			   delete tmpbuf;
			   tmpbuf = NULL;
			   size = 0;

			   ::ioctl(static_cast<Socket*>(evs[i].data.ptr)->Getfd(), FIONREAD, &size);
			   if (!size){
			   datawaiting = false;
			   tmpbuf = NULL;
			   continue;
			   }

			   tmpbuf = new char[size + 1];

			   if (!tmpbuf) {
			   std::cout << WARN << "[WebServer::_waitSrvs()] Bad Alloc" << std::endl;
			   continue ;
			   }

			   if (::read(static_cast<Socket*>(evs[i].data.ptr)->Getfd(), tmpbuf, size) != (int)size)
			   {
			   if (DEBUG)
			   std::cout << DBG << WARN << "[WebServer::_waitSrvs()] Read error" << std::endl;
			   continue ;
			   }

			   buf.reserve(size + 1);
			   for (size_t i = 0; i < size; i++)
			   buf.push_back(tmpbuf[i]);

			   }

			   HttpRequest req(buf, static_cast<Socket*>(evs[i].data.ptr)->GetSrvPort(), const_cast<char*>(static_cast<Socket*>(evs[i].data.ptr)->InetNtoa(static_cast<Socket*>(evs[i].data.ptr)->GetSin()->sin_addr.s_addr).c_str()));
			   HttpResponse res(req);

			   if (DEBUG)
			   std::cout << DBG << "[WebServer::Wait] Received and parsed request: " << std::endl << req << std::endl;
			   write(static_cast<Socket*>(evs[i].data.ptr)->Getfd(), res.getResponse().c_str(), res.getResponse().size());

			   ::close(static_cast<Socket*>(evs[i].data.ptr)->Getfd());
			   _epoll.Ctl(EPOLL_CTL_DEL, static_cast<Socket*>(evs[i].data.ptr)->Getfd(), NULL);
			   if (DEBUG)
			   std::cout << DBG << "[WebServer::_wait] _clients.size(): " << _clients.size() << std::endl;
			   FOREACH_VECTOR(Socket*, _clients, it){
			   if (*it == evs[i].data.ptr) _clients.erase(it);
			   }
			   delete static_cast<Socket*>(evs[i].data.ptr);
			   if (tmpbuf)
			   delete tmpbuf;
			   */
		}
	}

	FOREACH_VECTOR(Socket*, this->_clients, it){ delete *it; }
	for (int i = 0; i < MAX_EVENT; i++)
		if (tmpbufs[i])
			delete tmpbufs[i];
	return (STATUS_OK);
}
