#include "http_utils.hpp"
#include "webserver.hpp"
#include <cstring>
#include <fcntl.h>
#include <sys/epoll.h>
#include <iostream>

t_status	WebServer::_setupEpoll(void)
{
	_epoll.Create((int)EPOLL_CLOEXEC);

	epoll_event ev;

	memset(&ev, 0, sizeof(ev));

	for (std::vector<HttpServer*>::iterator it = this->_srv.begin(); it != this->_srv.end(); it++) {
		ev.events = EPOLLIN;
		ev.data.fd = (*it)->getSocket().Getfd();
		fcntl((*it)->getSocket().Getfd(), F_SETFD, FD_CLOEXEC);
		_epoll.Ctl(EPOLL_CTL_ADD, (*it)->getSocket().Getfd(), &ev);
	}

	return (STATUS_OK);
}
