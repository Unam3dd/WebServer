#include "http_config.hpp"
#include "http_colors.hpp"
#include "http_server.hpp"
#include "http_utils.hpp"
#include "webserver.hpp"
#include <new>
#include <vector>
#include <iostream>

static std::vector<port_t> _getUniquePorts(std::vector<HttpServerConfig*>& configs){
	std::vector<port_t> ports;

	for (std::vector<HttpServerConfig*>::iterator it = configs.begin(); it != configs.end(); it++)
	{
		for (std::vector<port_t>::iterator itp = (*it)->GetServerPorts().begin(); itp != (*it)->GetServerPorts().end(); itp++)
		{
			if (std::find(ports.begin(), ports.end(), *itp) == ports.end())
				ports.push_back(*itp);
		}
	}
	return (ports);
}

t_status	WebServer::_setupSrvs(void)
{
	HttpServer			*ptr = NULL;
	std::vector<port_t> ports = _getUniquePorts(this->_configs);

	for (std::vector<port_t>::iterator it = ports.begin(); it != ports.end(); it++) {
		try {
			ptr = new HttpServer("0.0.0.0", *it);
			_srv.push_back(ptr);
		} catch (std::exception &e) {
			std::cerr << FAIL << "[WebServer::_setupSrvs] Cannot bind to port: " << *it << RESET << std::endl;
			return (STATUS_FAIL);
		}
	}
	
	if (DEBUG)
	{
		std::cout << DBG << "[WebServer::_setupSrvs]"; PRINT_VECTOR_PORTS(ports, std::cout); std::cout << std::endl;
	}
	return (STATUS_OK);
}
