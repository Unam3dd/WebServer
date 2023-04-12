#include "http_response.hpp"
#include "http_colors.hpp"
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <sys/stat.h>

/*
 * @brief: prepare the response for a GET request. checks if the request is 
 * a directory or a file. if it's a directory, it checks if directory listing
 * is enabled. if it's a file, it checks if the user has the right to read it.
 * then it populates the response as needed, setting the status code and the 
 * body of the response.
 *
 * @return: void
 */
void	HttpResponse::_prepareGetResponse(){
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
	
	if (path.find(".") != std::string::npos)
	{
		std::string extension = path.substr(path.find_last_of("."), path.length() - path.find_last_of("."));
		if (_reqcfg && _reqcfg->GetCgi().size() != 0)
		{
			FOREACH_MAP_STR_CONST(_reqcfg->GetCgi(), cfgcgi){
				if (cfgcgi->first == extension){
					_processCgi(cfgcgi->second, path);
					this->_fullresponse = _cgibuf;
					return ;
				}
			}
		}
		else{
			FOREACH_MAP_STR_CONST(_srvcfg->GetCgi(), cfgcgi){
				if (cfgcgi->first == extension){
					_processCgi(cfgcgi->second, path);
					this->_fullresponse = _cgibuf;
					return ;
				}
			}
		}
	}
	isdir = _isDirectory(path);

	if (!isdir){
		if (DEBUG)
		{
			std::cout << DBG << "[_prepareGetResponse] request is not a directory" << std::endl;
			std::cout << DBG << "[_prepareGetResponse] path: " << path << std::endl;
			std::cout << DBG << "[_prepareGetResponse] docroot: " << docroot << std::endl;
		}
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
	else{
		if (stat(path.c_str(), &st) < 0)
		{
			this->_status = HTTP_STATUS_NOT_FOUND;
			this->_body = this->_getErrorPageContent(this->_status);
			this->_contenttype = "text/html";
			return;
		}
		if (DEBUG)
			std::cout << DBG << "[_prepareGetResponse] request: "<< path << " is a directory" << std::endl;
		if ((_reqcfg && !_reqcfg->GetDirList()) || (!_reqcfg && !_srvcfg->GetDirList()))
		{
			if (DEBUG)
				std::cout << DBG << RED <<"[_prepareGetResponse] directory listing is disabled" << RESET << std::endl;
			this->_status = HTTP_STATUS_FORBIDDEN;
			this->_body = this->_getErrorPageContent(this->_status);
			this->_contenttype = "text/html";
			return;
		}
		if (DEBUG)
			std::cout << DBG << "[_prepareGetResponse] directory listing is enabled" << std::endl;
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
}

