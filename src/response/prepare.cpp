#include "http_response.hpp"
#include "http_colors.hpp"
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <sys/stat.h>

void	HttpResponse::_prepareGetResponse(){
	struct stat st;
	std::string docroot;
	std::string path;
	std::string uri = this->_request.getUri();
	bool		isdir = true;

	if (!_reqcfg)
		docroot = _srvcfg->GetRoot();
	else
		docroot = _reqcfg->GetRoot();
	path = docroot + uri;

	std::memset(&st, 0, sizeof(st));
	stat(path.c_str(), &st);
	if (FILE_EXISTS(path.c_str()) || !S_ISDIR(st.st_mode))
		isdir = false;
	else if (*path.rbegin() == '/' && FILE_EXISTS((path.substr(0, path.length() - 1).c_str()))){
		path = path.substr(0, path.length() - 1);
		isdir = false;
	}
	else if (_reqcfg && _reqcfg->GetIndexs().size() > 0)
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

