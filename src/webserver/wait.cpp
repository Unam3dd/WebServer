#include "http_utils.hpp"
#include "http_colors.hpp"
#include "webserver.hpp"
#include <sys/epoll.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

t_status	WebServer::_acceptClient(ev_t *e)
{
	Socket	*client = NULL;
	ev_t	tev;

	if (!e) return (STATUS_FAIL);

	FOREACH_VECTOR(HttpServer*, this->_srv){
		if (e->data.fd == (*it)->getSocket().Getfd()) {
			client = (*it)->getSocket().Accept();
			if (client) {
				(*it)->getClients().push_back(client);
				tev.data.ptr = client;
				tev.events = EPOLLIN;
				this->_epoll.Ctl(EPOLL_CTL_ADD, client->Getfd(), &tev);
				std::cout << SUCCESS << "[WebServer::Wait] New client Accepted ! " << client->InetNtoa(client->GetSin()->sin_addr.s_addr) << ":" << client->Ntohs(client->GetSin()->sin_port) << std::endl;
				return (STATUS_OK);
			}
		}
	}

	return (STATUS_FAIL);
}

t_status	WebServer::_waitSrvs(void)
{
	char	buf[0x10000];
	epoll_event evs[MAX_EVENT];
	int	nfds = 0;
	int i = 0;

	// TODO: Setup Signals

	while (1)
	{
		nfds = _epoll.Wait(evs, MAX_EVENT, -1);

		for (i = 0; i < nfds; i++) {

			if (_acceptClient(&evs[i]) == STATUS_OK)
				continue ;

			if (DEBUG)
				std::cout << DBG << "[WebServer::Wait] ON A DE LA DATA A LIRE" << std::endl;

			memset(buf, 0, sizeof(buf));
			if (::read(static_cast<Socket*>(evs[i].data.ptr)->Getfd(), buf, sizeof(buf)) < 0)
				return (STATUS_FAIL);

			std::cout << buf << std::endl;

			write(static_cast<Socket*>(evs[i].data.ptr)->Getfd(), "hello world\n", 12);

			::close(static_cast<Socket*>(evs[i].data.ptr)->Getfd());
			_epoll.Ctl(EPOLL_CTL_DEL, static_cast<Socket*>(evs[i].data.ptr)->Getfd(), NULL);
			delete static_cast<Socket*>(evs[i].data.ptr);
		}
	}

	return (STATUS_OK);
}
