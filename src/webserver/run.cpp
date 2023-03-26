#include "http_utils.hpp"
#include "webserver.hpp"
#include "http_colors.hpp"
#include <iostream>
t_status	WebServer::Run(void)
{
	t_status status = STATUS_OK;

	status = this->_setupSrvs();
	if (status != STATUS_OK)
	{
		std::cerr << FAIL << "[WebServer::Run] Cannot setup servers" << RESET << std::endl;
		return (status);
	}
	status = this->_listenSrvs();
	if (status != STATUS_OK)
	{
		std::cerr << FAIL << "[WebServer::Run] Cannot listen servers" << RESET << std::endl;
		return (status);
	}
	status = this->_setupEpoll();
	if (status != STATUS_OK)
	{
		std::cerr << FAIL << "[WebServer::Run] Cannot setup epoll" << RESET << std::endl;
		return (status);
	}
	status = this->_waitSrvs();
	if (status != STATUS_OK)
	{
		std::cerr << FAIL << "[WebServer::Run] Cannot wait servers" << RESET << std::endl;
		return (status);
	}
	return (STATUS_OK);
}
