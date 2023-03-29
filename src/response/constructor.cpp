#include "http_response.hpp"
#include "http_utils.hpp"
#include "http_colors.hpp"
#include "webserver.hpp"
#include <iostream>

HttpServerConfig*	HttpResponse::_getSrvConfig(const std::string& host, port_t port){
	std::vector<HttpServerConfig*> srvs = SG_WebServer(NULL)->GetServers();

	FOREACH_VECTOR(HttpServerConfig*, srvs, cfg){
		FOREACH_VECTOR(port_t, (*cfg)->GetServerPorts(), prt){
			FOREACH_VECTOR(std::string, (*cfg)->GetServerNames(), name){
				if (host == *name && port == *prt)
					return (*cfg);
			}
		}
		FOREACH_VECTOR(port_t, (*cfg)->GetServerPorts(), prt){
			if (port == *prt)
				return (*cfg);
		}
		FOREACH_VECTOR(std::string, (*cfg)->GetServerNames(), name){
			if (host == *name)
				return (*cfg);
		}
	}
	return srvs[0];
}

HttpRequestConfig* HttpResponse::_getReqConfig(const HttpServerConfig* cfg, const std::string& uri){
	std::vector<HttpRequestConfig*> reqs = cfg->GetRequestConfigs();

	FOREACH_VECTOR(HttpRequestConfig*, reqs, req){
		if (uri.substr(0, (*req)->GetScope().length()) == (*req)->GetScope())
			return (*req);
	}
	return NULL;
}

HttpResponse::HttpResponse(const HttpRequest &req) : _request(req)
{
	_srvcfg = _getSrvConfig(_request.getHeaders().at("host"), _request.getPort());
	_reqcfg = _getReqConfig(_srvcfg, _request.getUri());
	_status = HTTP_STATUS_OK;

	this->writeResponse("HTTP/1.1 200 OK\r\nContent-Length: 20\r\n\r\n<h1>hello world</h1>\r\n");

	if (DEBUG)
	{
		std::cout << DBG << "[HttpResponse::HttpResponse()] Host: " << _request.getHeaders().at("host") << std::endl;
		std::cout << DBG << "[HttpResponse::HttpResponse()] Port: " << _request.getPort() << std::endl;
		std::cout << DBG << "[HttpResponse::HttpResponse()] Uri: " << _request.getUri() << std::endl;
		std::cout << DBG << "[HttpResponse::HttpResponse()] Server config chosen: "; PRINT_VECTOR_STR(_srvcfg->GetServerNames(), std::cout); std::cout << std::endl;
		std::cout << DBG << "[HttpResponse::HttpResponse()] Request config chosen: ";
		_reqcfg == NULL ? std::cout << "none" : std::cout << _reqcfg->GetScope(); std::cout << std::endl;
	}
}
