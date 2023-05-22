/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:10:21 by ldournoi          #+#    #+#             */
/*   Updated: 2023/05/23 00:43:24 by ldournoi         ###   ########.fr       */
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

t_status	WebServer::_acceptClient(ev_t *e)
{
	Socket	*client = NULL;
	ev_t	tev;

	if (!e) return (STATUS_FAIL);

	FOREACH_VECTOR(HttpServer*, this->_srv, srv)
	{
		if (e->data.fd == (*srv)->getSocket().Getfd())
		{
			client = (*srv)->getSocket().Accept();
			if (client) 
			{
				tev.data.ptr = client;
				tev.events = EPOLLIN;
				this->_epoll.Ctl(EPOLL_CTL_ADD, client->Getfd(), &tev);
				client->SetSrvPort((*srv)->getPort());
				(*srv)->getClients().push_back(client);
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
				sock_fd = static_cast<Socket*>(evs[i].data.ptr)->Getfd();
				::ioctl(sock_fd, FIONREAD, &size);
				if (!size){
					continue;
				}
				
				if (DEBUG)
					std::cout << DBG << "[WebServer::_waitSrvs()] EPOLLIN : size of request: " << size << std::endl;

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
					std::cout << DBG << "[WebServer::_waitSrvs()] EPOLLIN : request: " << std::endl << bufs[sock_fd % MAX_EVENT] << std::endl;
				}

				delete[] tmpbufs[sock_fd % MAX_EVENT];
				tmpbufs[sock_fd % MAX_EVENT] = NULL;

				if (   bufs[sock_fd % MAX_EVENT].find("\r\n\r\n") != std::string::npos
					|| bufs[sock_fd % MAX_EVENT].find("\n\n") != std::string::npos) {
					if (DEBUG)
						std::cout << DBG << "[WebServer::_waitSrvs()] EPOLLIN : End of header received. Setting EPOLLOUT" << std::endl;
					evs[i].events = EPOLLOUT;
					_epoll.Ctl(EPOLL_CTL_MOD, sock_fd, &evs[i]);
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

	FOREACH_VECTOR(Socket*, _clients, it){ delete *it; }
	for (int i = 0; i < MAX_EVENT; i++)
		if (tmpbufs[i])
			delete tmpbufs[i];
	return (STATUS_OK);
}
