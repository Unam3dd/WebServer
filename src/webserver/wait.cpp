/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:10:21 by ldournoi          #+#    #+#             */
/*   Updated: 2023/04/18 20:43:39 by ldournoi         ###   ########.fr       */
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

	FOREACH_VECTOR(HttpServer*, this->_srv, it){
		if (e->data.fd == (*it)->getSocket().Getfd()) {
			client = (*it)->getSocket().Accept();
			if (client) {
				(*it)->getClients().push_back(client);
				tev.data.ptr = client;
				client->SetSrvPort((*it)->getPort());
				tev.events = EPOLLIN;
				this->_epoll.Ctl(EPOLL_CTL_ADD, client->Getfd(), &tev);
				std::cout << SUCCESS << "[WebServer::Wait] New client Accepted ! " << client->InetNtoa(client->GetSin()->sin_addr.s_addr) << ":" << client->Ntohs(client->GetSin()->sin_port) << std::endl;
				_clients.push_back(client);
				return (STATUS_OK);
			}
		}
	}

	return (STATUS_FAIL);
}

t_status	WebServer::_waitSrvs(void)
{
	std::string buf;
	char	*tmpbuf = NULL;
	size_t	size = 0;
	epoll_event evs[MAX_EVENT];
	int	nfds = 0;
	int i = 0;

	// TODO: Setup Signals
	sig_setup();
	this->_run = 1;

	while (_run)
	{
		nfds = _epoll.Wait(evs, MAX_EVENT, -1);

		for (i = 0; i < nfds; i++) {

			tmpbuf = NULL;
			size = 0;
			buf.clear();

			if (_acceptClient(&evs[i]) == STATUS_OK)
				continue;

			bool datawaiting = true;
			while (datawaiting)
			{
				if (tmpbuf)
					delete tmpbuf;
				tmpbuf = NULL;
				size = 0;

				::ioctl(static_cast<Socket*>(evs[i].data.ptr)->Getfd(), FIONREAD, &size);
				if (!size)
					datawaiting = false;
				
				tmpbuf = new char[size + 1];

				if (!tmpbuf) {
					std::cout << WARN << "[WebServer::_waitSrvs()] Bad Alloc" << std::endl;
					continue ;
				}

				if (::read(static_cast<Socket*>(evs[i].data.ptr)->Getfd(), tmpbuf, size) != (int)size)
					return (STATUS_FAIL);
				
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
			delete tmpbuf;
		}
	}

	FOREACH_VECTOR(Socket*, _clients, it){ delete *it; }

	return (STATUS_OK);
}
