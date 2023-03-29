#include "http_response.hpp"
#include "http_utils.hpp"
#include "http_colors.hpp"
#include "http_status.hpp"
#include "utils.hpp"
#include "webserver.hpp"
#include <iostream>
#include <cstdlib>

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

void HttpResponse::_generateResponse(void){
	time_t now = time(NULL);
	struct tm *t = gmtime(&now);
	char buf[0x100];
	strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S %Z", t);

	this->_fullresponse += "HTTP/1.1 " + NumberToString(_status) + " " + get_http_status_msg(_status) + "\r\n";
	this->_fullresponse += "Server: WebServ version " + std::string(VERSION) + "\r\n";
	this->_fullresponse += "Date: " + std::string(buf) + "\r\n";
	_contenttype != "" ? this->_fullresponse += "Content-Type: " + this->_contenttype + "\r\n" : "";
	_body.size() != 0  ? this->_fullresponse += "Content-Length: " + NumberToString(this->_body.size()) + "\r\n" : "";
	this->_fullresponse += "Connection: close\r\n";
	this->_fullresponse += "\r\n";
	this->_fullresponse += this->_body;
}

HttpResponse::HttpResponse(const HttpRequest &req) : _request(req)
{
	_srvcfg = _getSrvConfig(_request.getHeaders().at("host"), _request.getPort());
	_reqcfg = _getReqConfig(_srvcfg, _request.getUri());
	_status = HTTP_STATUS_OK;
	_contenttype = "";

	if (_request.getVersion() != "HTTP/1.1"){
		_status = HTTP_STATUS_VERSION_NOT_SUPPORTED;
		this->_contenttype = "";
		this->_generateResponse();
		return ;
	}
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
