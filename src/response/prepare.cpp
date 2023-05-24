#include "http_response.hpp"
#include "http_colors.hpp"
#include "http_status.hpp"
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <sys/stat.h>

void	HttpResponse::_prepareResponse(){
	struct stat st;
	std::string docroot;
	std::string path;
	std::string uri = this->_request.getUri();
	bool		isdir = true;

	if (!_reqcfg)
		docroot = _srvcfg->GetRoot();
	else
	{
		// if the request belongs to a location block, we need to remove the scope
		uri = uri.substr(_reqcfg->GetScope().length(), uri.length() - _reqcfg->GetScope().length());
		docroot = _reqcfg->GetRoot();
	}
	path = docroot + uri;

	isdir = _isDirectory(path);

	if (path.find(".") != std::string::npos)
	{
		std::string extension = path.substr(path.find_last_of("."), path.length() - path.find_last_of("."));
		std::map<std::string,std::string> cgi;
		if (_reqcfg && _reqcfg->GetCgi().size() != 0)
			cgi = _reqcfg->GetCgi();
		else
			cgi = _srvcfg->GetCgi();
		FOREACH_MAP_STR(cgi, cfgcgi){
			if (cfgcgi->first == extension){
				if (_processCgi(cfgcgi->second, path))
				{
					this->_status = HTTP_STATUS_BAD_GATEWAY;
					this->_body = _getErrorPageContent(this->_status);
					this->_contenttype = "text/html";
					_generateResponse();
					return;
				}
				_generateResponseCgi();
				return ;
			}
		}
	}

	if (!isdir && (this->_request.getMethod() == GET || this->_request.getMethod() == POST)){
		#if DEBUG
		{
			std::cout << DBG << "[_prepareGetResponse] request is not a directory" << std::endl;
			std::cout << DBG << "[_prepareGetResponse] path: " << path << std::endl;
			std::cout << DBG << "[_prepareGetResponse] docroot: " << docroot << std::endl;
		}
		#endif
		if (stat(path.c_str(), &st) < 0)
		{
			this->_status = HTTP_STATUS_NOT_FOUND;
			this->_body = this->_getErrorPageContent(this->_status);
			this->_contenttype = "text/html";
			return;
		}
		if (!(st.st_mode & S_IRUSR))
		{
			this->_status = HTTP_STATUS_FORBIDDEN;
			this->_body = this->_getErrorPageContent(this->_status);
			this->_contenttype = "text/html";
			return;
		}
		File content(path.c_str(), O_RDONLY, S_IRUSR);
		this->_status = HTTP_STATUS_OK;
		this->_contenttype = this->_getContentType(path);
		APPEND_FILE_TO_STRING(this->_body, content);
	}
	else if (!isdir && this->_request.getMethod() == DELETE){
		if (stat(path.c_str(), &st) < 0)
		{
			this->_status = HTTP_STATUS_NOT_FOUND;
			this->_body = this->_getErrorPageContent(this->_status);
			this->_contenttype = "text/html";
			return;
		}
		if (!(st.st_mode & S_IWUSR))
		{
			this->_status = HTTP_STATUS_FORBIDDEN;
			this->_body = this->_getErrorPageContent(this->_status);
			this->_contenttype = "text/html";
			return;
		}
		if (remove(path.c_str()) < 0)
		{
			this->_status = HTTP_STATUS_INTERNAL_SERVER_ERROR;
			this->_body = this->_getErrorPageContent(this->_status);
			this->_contenttype = "text/html";
			return;
		}
		this->_status = HTTP_STATUS_NO_CONTENT;
		this->_body = "";
		this->_contenttype = "text/html";
	}
	else if (isdir && (this->_request.getMethod() == GET || this->_request.getMethod() == POST)){
		if (stat(path.c_str(), &st) < 0)
		{
			this->_status = HTTP_STATUS_NOT_FOUND;
			this->_body = this->_getErrorPageContent(this->_status);
			this->_contenttype = "text/html";
			return;
		}
		#if DEBUG
			std::cout << DBG << "[_prepareGetResponse] request: "<< path << " is a directory" << std::endl;
		#endif
		if ((_reqcfg && !_reqcfg->GetDirList()) || (!_reqcfg && !_srvcfg->GetDirList()))
		{
			if (DEBUG)
				std::cout << DBG << RED <<"[_prepareGetResponse] directory listing is disabled" << RESET << std::endl;
			this->_status = HTTP_STATUS_FORBIDDEN;
			this->_body = this->_getErrorPageContent(this->_status);
			this->_contenttype = "text/html";
			return;
		}
		#if DEBUG
			std::cout << DBG << "[_prepareGetResponse] directory listing is enabled" << std::endl;
		#endif
		Directory dir(path.c_str());
		std::vector<std::string> files = dir.getFiles();
		this->_status = HTTP_STATUS_OK;
		this->_body = "<html><head><title>Index of " + uri + "</title></head><body><h1>Index of " + uri + "</h1><hr><pre>";
		FOREACH_VECTOR_CONST(std::string, files, file){
			stat((path + *file).c_str(), &st);
			if (st.st_mode & S_IFDIR)
				this->_body += "<a href=\"" + uri + *file + "/\">" + *file + "/</a><br>";
			else
				this->_body += "<a href=\"" + uri + *file + "\">" + *file + "</a><br>";
		}
		this->_body += "</pre><hr></body></html>";
		this->_contenttype = "text/html";
	}
	else if (isdir && this->_request.getMethod() == DELETE){
		if (stat(path.c_str(), &st) < 0)
		{
			this->_status = HTTP_STATUS_NOT_FOUND;
			this->_body = this->_getErrorPageContent(this->_status);
			this->_contenttype = "text/html";
			return;
		}
		if (!(st.st_mode & S_IWUSR))
		{
			this->_status = HTTP_STATUS_FORBIDDEN;
			this->_body = this->_getErrorPageContent(this->_status);
			this->_contenttype = "text/html";
			return;
		}
		if (rmdir(path.c_str()) < 0)
		{
			this->_status = HTTP_STATUS_INTERNAL_SERVER_ERROR;
			this->_body = this->_getErrorPageContent(this->_status);
			this->_contenttype = "text/html";
			return;
		}
		this->_status = HTTP_STATUS_NO_CONTENT;
		this->_body = "";
		this->_contenttype = "text/html";
	}
}
