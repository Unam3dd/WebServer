#include "http_utils.hpp"
#include "webserver.hpp"

t_status	WebServer::_listenSrvs(void)
{
	FOREACH_VECTOR(HttpServer*, this->_srv, srv)
		(*srv)->Listen(SOMAXCONN);
	return (STATUS_OK);
}
