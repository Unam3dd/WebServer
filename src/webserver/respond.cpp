#include "webserver.hpp"
#include "http_response.hpp"
#include "http_utils.hpp"


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
