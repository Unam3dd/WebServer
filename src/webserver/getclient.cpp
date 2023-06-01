#include "webserver.hpp"
#include "utils.hpp"

Socket* WebServer::_getClientSocketFromFd(int fd)
{
	FOREACH_VECTOR(Socket*, this->_clients, it){
		if ((*it)->Getfd() == fd || this->_timerfds[(*it)->Getfd()] == fd)
			return (*it);
	}

	return (NULL);
}

Socket* WebServer::_getClientSocketFromEvent(struct epoll_event* event)
{
	if ((unsigned long long)event->data.fd < lowest_heap_address())
		return (this->_getClientSocketFromFd(event->data.fd));
	else
		return (static_cast<Socket*>(event->data.ptr));

	return (NULL);
}
