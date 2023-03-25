#include "http_utils.hpp"
#include "webserver.hpp"
#include <cstring>
#include <sys/epoll.h>

t_status	WebServer::_setupEpoll(void)
{
	_epoll.Create(0);

	epoll_event ev;

	memset(&ev, 0, sizeof(ev));

	for (std::vector<HttpServer*>::iterator it = this->_srv.begin(); it != this->_srv.end(); it++) {
		ev.events = EPOLLIN;
		ev.data.fd = (*it)->getSocket().Getfd();
		_epoll.Ctl(EPOLL_CTL_ADD, (*it)->getSocket().Getfd(), &ev);
	}

	return (STATUS_OK);
}
