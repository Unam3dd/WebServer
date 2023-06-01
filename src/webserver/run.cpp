#include "http_utils.hpp"
#include "webserver.hpp"
#include "logger.hpp"
#include <iostream>
t_status	WebServer::Run(void)
{
	t_status status = STATUS_OK;

	status = this->_setupSrvs();
	if (status != STATUS_OK)
	{
		logz.logerr(L_ERROR | L_BYPASS, "Cannot setup servers");
		return (status);
	}
	status = this->_listenSrvs();
	if (status != STATUS_OK)
	{
		logz.logerr(L_ERROR | L_BYPASS, "Cannot listen servers");
		return (status);
	}
	status = this->_setupEpoll();
	if (status != STATUS_OK)
	{
		logz.logerr(L_ERROR | L_BYPASS, "Cannot setup epoll");
		return (status);
	}
	status = this->_waitSrvs();
	if (status != STATUS_OK)
	{
		logz.logerr(L_ERROR | L_BYPASS, "Cannot wait servers");
		return (status);
	}
	return (STATUS_OK);
}
