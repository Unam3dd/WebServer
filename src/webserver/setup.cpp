#include "http_config.hpp"
#include "logger.hpp"
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
	std::vector<port_t>	ports = _getUniquePorts(this->_configs);
	std::string			tmp = "";

	FOREACH_VECTOR(port_t, ports, port){
		try {
			ptr = new HttpServer("0.0.0.0", *port);
			_srv.push_back(ptr);
		} catch (std::exception &e) {
			logz.logerr(L_ERROR | L_BYPASS, "Cannot bind to port: " + logz.itoa(*port));
			return (STATUS_FAIL);
		}
	}
	for (std::vector<port_t>::iterator it = ports.begin(); it != ports.end(); ++it)
	{
		tmp += logz.itoa(*it) + " ";
		if (it == ports.end())
			tmp += " ";
	}
	logz.log(L_DEBUG, tmp);
	return (STATUS_OK);
}
