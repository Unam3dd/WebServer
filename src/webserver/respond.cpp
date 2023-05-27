#include "webserver.hpp"
#include "http_response.hpp"
#include "http_utils.hpp"
#include "utils.hpp"
#include <fstream>


void	WebServer::_respondAndClean(http_status_code_t status, int fd){
	Socket* client = this->_getClientSocketFromFd(fd);

	HttpResponse response(status);
	write(client->Getfd(), response.getResponse().c_str(), response.getResponse().length());
	
	close(client->Getfd());
	this->_epoll.Ctl(EPOLL_CTL_DEL, client->Getfd(), NULL);

	close(this->_timerfds[client->Getfd()]);
	this->_epoll.Ctl(EPOLL_CTL_DEL, this->_timerfds[client->Getfd()], NULL);
	this->_timerfds.erase(client->Getfd());
}

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
