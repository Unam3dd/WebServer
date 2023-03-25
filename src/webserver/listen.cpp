#include "http_utils.hpp"
#include "webserver.hpp"

t_status	WebServer::_listenSrvs(void)
{
	for (std::vector<HttpServer*>::iterator it = this->_srv.begin(); it != this->_srv.end(); it++)
		(*it)->Listen(SOMAXCONN);
	return (STATUS_OK);
}
