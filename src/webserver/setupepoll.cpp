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

	FOREACH_VECTOR(HttpServer*, this->_srv, srv) {
		ev.events = EPOLLIN;
		ev.data.fd = (*srv)->getSocket().Getfd();
		fcntl((*srv)->getSocket().Getfd(), F_SETFD, FD_CLOEXEC);
		_epoll.Ctl(EPOLL_CTL_ADD, (*srv)->getSocket().Getfd(), &ev);
	}

	return (STATUS_OK);
}
