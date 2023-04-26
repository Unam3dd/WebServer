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

	FOREACH_VECTOR(HttpServerConfig*, configs, cfg)
	{
		FOREACH_VECTOR(port_t, (*cfg)->GetServerPorts(), port)
		{
			if (std::find(ports.begin(), ports.end(), *port) == ports.end())
				ports.push_back(*port);
		}
	}
	return (ports);
}

t_status	WebServer::_setupSrvs(void)
{
	HttpServer			*ptr = NULL;
	std::vector<port_t> ports = _getUniquePorts(this->_configs);

	FOREACH_VECTOR(port_t, ports, port){
		try {
			ptr = new HttpServer("0.0.0.0", *port);
			_srv.push_back(ptr);
		} catch (std::exception &e) {
			std::cerr << FAIL << "[WebServer::_setupSrvs] Cannot bind to port: " << *port << RESET << std::endl;
			return (STATUS_FAIL);
		}
	}
	
	if (DEBUG)
		std::cout << DBG << "[WebServer::_setupSrvs]"; PRINT_VECTOR_PORTS(ports, std::cout); std::cout << std::endl;
	return (STATUS_OK);
}
