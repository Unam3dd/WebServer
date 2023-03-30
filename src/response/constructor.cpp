#include "http_response.hpp"
#include "http_utils.hpp"
#include "http_colors.hpp"
#include "http_status.hpp"
#include "utils.hpp"
#include "webserver.hpp"
#include <iostream>
#include <cstdlib>
#include <sys/stat.h>

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

std::string	HttpResponse::_getErrorPageContent(http_status_code_t httpstatus){
	std::string	root;
	std::string path;
	std::string fullpath;
	errpagecode_t status;

	if (httpstatus == HTTP_STATUS_BAD_REQUEST)
		status = E400;
	else if (httpstatus == HTTP_STATUS_UNAUTHORIZED)
		status = E401;
	else if (httpstatus == HTTP_STATUS_FORBIDDEN)
		status = E403;
	else if (httpstatus == HTTP_STATUS_NOT_FOUND)
		status = E404;
	else if (httpstatus == HTTP_STATUS_METHOD_NOT_ALLOWED)
		status = E405;
	else if (httpstatus == HTTP_STATUS_INTERNAL_SERVER_ERROR)
		status = E500;
	else if (httpstatus == HTTP_STATUS_NOT_IMPLEMENTED)
		status = E501;
	else if (httpstatus == HTTP_STATUS_VERSION_NOT_SUPPORTED)
		status = E505;
	if (_reqcfg)
	{
		if (_reqcfg->GetErrorPages()[status].path == "default" && _srvcfg->GetErrorPages()[status].path == "default")
			return (SG_DefaultErrorPages(status));
		_reqcfg->GetRoot() == "" ? root = _srvcfg->GetRoot() : root = _reqcfg->GetRoot();
		_reqcfg->GetErrorPages()[status].path == "default" ? path = _srvcfg->GetErrorPages()[status].path : path = _reqcfg->GetErrorPages()[status].path;
		fullpath = root + path;
		if (!FILE_EXISTS(fullpath.c_str())){
			return (SG_DefaultErrorPages(status));
		}
		struct stat st;
		stat(fullpath.c_str(), &st);
		if (st.st_mode & S_IRUSR)
		{
			File content(fullpath.c_str(), O_RDONLY, S_IRUSR);
			return (content.getData());
		}
		else{
			return (SG_DefaultErrorPages(status));
		}
	}
	if (DEBUG)
		std::cout << DBG << "[_getErrorPageContent] _srvcfg: " << *_srvcfg << std::endl;
	if (_srvcfg->GetErrorPages()[status].path == "default")
		return (SG_DefaultErrorPages(status));
	root = _srvcfg->GetRoot();
	path = _srvcfg->GetErrorPages()[status].path;
	fullpath = root + path;
	if (!FILE_EXISTS(fullpath.c_str())){
		return (SG_DefaultErrorPages(status));
	}
	struct stat st;
	stat(fullpath.c_str(), &st);
	if (st.st_mode & S_IRUSR)
	{
		File content(fullpath.c_str(), O_RDONLY, S_IRUSR);
		return (content.getData());
	}
	else{
		return (SG_DefaultErrorPages(status));
	}
	return ("");
}

std::string HttpResponse::_getContentType(const std::string& path){
	std::string extension = path.substr(path.find_last_of("."), path.length() - path.find_last_of("."));

	return (SG_GetContentType(extension));
}

void	HttpResponse::_prepareGetResponse(){
	std::string docroot;
	std::string path;
	std::string uri = this->_request.getUri();
	bool		isdir = true;

	if (!_reqcfg)
		docroot = _srvcfg->GetRoot();
	else
		docroot = _reqcfg->GetRoot();
	path = docroot + uri;

	if (path == "/" || path.at(path.length() - 1) == '/')
	{
		if (_reqcfg && _reqcfg->GetIndexs().size() > 0)
		{
			FOREACH_VECTOR_CONST(std::string, _reqcfg->GetIndexs(), index){
				if (FILE_EXISTS((path + *index).c_str()))
				{
					path += *index;
					isdir = false;
					break;
				}
			}
		}
		else if (_srvcfg->GetIndexs().size() > 0)
		{
			FOREACH_VECTOR_CONST(std::string, _srvcfg->GetIndexs(), index){
				if (FILE_EXISTS((path + *index).c_str()))
				{
					path += *index;
					isdir = false;
					break;
				}
			}
		}
	}
	else
		isdir = false;
	std::cout << "path: " << path << std::endl;
	if (!isdir){
		if (DEBUG)
		{
			std::cout << DBG << "[_prepareGetResponse] request is not a directory" << std::endl;
			std::cout << DBG << "[_prepareGetResponse] path: " << path << std::endl;
			std::cout << DBG << "[_prepareGetResponse] docroot: " << docroot << std::endl;
		}
		struct stat st;
		if (stat(path.c_str(), &st) < 0)
		{
			this->_status = HTTP_STATUS_NOT_FOUND;
			this->_body = this->_getErrorPageContent(this->_status);
			this->_contenttype = "text/html";
			return;
		}
		if (st.st_mode & S_IRUSR)
		{
			File content(path.c_str(), O_RDONLY, S_IRUSR);

			this->_status = HTTP_STATUS_OK;
			this->_body = content.getData();
			this->_contenttype = this->_getContentType(path);
		}
		else
		{
			this->_status = HTTP_STATUS_FORBIDDEN;
			this->_body = this->_getErrorPageContent(this->_status);
			this->_contenttype = "text/html";
		}
	}
	else{
		if (DEBUG)
		{
			std::cout << DBG << "[_prepareGetResponse] request: "<< path << " is a directory" << std::endl;
		}
	}
}

HttpResponse::HttpResponse(const HttpRequest &req) : _request(req)
{
	_srvcfg = _getSrvConfig(_request.getHeaders().at("host"), _request.getPort());
	_reqcfg = _getReqConfig(_srvcfg, _request.getUri());
	_status = HTTP_STATUS_OK;
	_contenttype = "";

	methods_t methods;
	_reqcfg ? methods = _reqcfg->GetMethods() : methods = _srvcfg->GetMethods();
	if (_request.getVersion() != "HTTP/1.0" && _request.getVersion() != "HTTP/1.1"){
		_status = HTTP_STATUS_VERSION_NOT_SUPPORTED;
		this->_contenttype = "";
		this->_generateResponse();
		return ;
	}
	if ((_request.getMethod() & GET && !(methods & GET)) ||
		(_request.getMethod() & POST && !(methods & POST)) ||
		(_request.getMethod() & PUT && !(methods & PUT)) ||
		(_request.getMethod() & DELETE && !(methods & DELETE)))
	{
		_status = HTTP_STATUS_METHOD_NOT_ALLOWED;
		this->_contenttype = "";
		this->_generateResponse();
		return ;
	}
	
	if (_request.getMethod() & GET){
		this->_prepareGetResponse();
		this->_generateResponse();
	}
	/*
	if (_request.getMethod() & POST){
		this->_preparePostResponse();
		this->_generateResponse();
		return ;
	}

	if (_request.getMethod() & PUT){
		this->_preparePutResponse();
		this->_generateResponse();
		return ;
	}

	if (_request.getMethod() & DELETE){
		this->_prepareDeleteResponse();
		this->_generateResponse();
		return ;
	}
	*/
	if (DEBUG)
	{
		std::cout << DBG << "[HttpResponse::HttpResponse()] Host: " << _request.getHeaders().at("host") << std::endl;
		std::cout << DBG << "[HttpResponse::HttpResponse()] Port: " << _request.getPort() << std::endl;
		std::cout << DBG << "[HttpResponse::HttpResponse()] Uri: " << _request.getUri() << std::endl;
		std::cout << DBG << "[HttpResponse::HttpResponse()] Server config chosen: "; PRINT_VECTOR_STR(_srvcfg->GetServerNames(), std::cout); std::cout << std::endl;
		std::cout << DBG << "[HttpResponse::HttpResponse()] Request config chosen: ";
		_reqcfg == NULL ? std::cout << "none" : std::cout << _reqcfg->GetScope(); std::cout << std::endl;
		std::cout << DBG << "[HttpResponse::HttpResponse()] Full response: " << std::endl << _fullresponse << std::endl;
	}
}
