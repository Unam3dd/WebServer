#include "http_utils.hpp"
#include "webserver.hpp"

t_status	WebServer::Run(void)
{
	this->_setupSrvs();
	this->_listenSrvs();
	this->_setupEpoll();
	this->_waitSrvs();
	return (STATUS_OK);
}
