#include "http_utils.hpp"
#include "http_colors.hpp"
#include "webserver.hpp"
#include <sys/epoll.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

t_status	WebServer::_waitSrvs(void)
{
	char	buf[0x10000];
	Socket	*client = NULL;
	epoll_event evs[MAX_EVENT];
	epoll_event	ev;
	int	nfds = 0;
	int i = 0;
	bool accepted = false;

	// TODO: Setup Signals

	while (1)
	{
		nfds = _epoll.Wait(evs, MAX_EVENT, -1);

		for (i = 0; i < nfds; i++) {
			FOREACH_VECTOR(HttpServer*, this->_srv){
				if (evs[i].data.fd == (*it)->getSocket().Getfd()) {
					client = (*it)->getSocket().Accept();
					if (client) {
						(*it)->getClients().push_back(client);
						ev.data.ptr = client;
						ev.events = EPOLLIN;
						_epoll.Ctl(EPOLL_CTL_ADD, client->Getfd(), &ev);
						if (DEBUG)
							std::cout << DBG << "[WebServer::Wait] New client Accepted ! " << client->InetNtoa(client->GetSin()->sin_addr.s_addr) << ":" << client->Ntohs(client->GetSin()->sin_port) << std::endl;
					}

					accepted = true;
					break ;
				}
			}

			if (accepted) {
				accepted = false;
				continue ;
			}

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
