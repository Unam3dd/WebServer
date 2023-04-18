#include "http_response.hpp"
#include "http_colors.hpp"
#include "http_status.hpp"
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
void	HttpResponse::_prepareDeleteResponse(){
	//struct stat st;
	std::string docroot;
	std::string path;
	std::string uri = this->_request.getUri();
	//bool		isdir = true;

	if (!_reqcfg)
		docroot = _srvcfg->GetRoot();
	else
	{
		// if the request belongs to a location block, we need to remove the scope
		uri = uri.substr(_reqcfg->GetScope().length(), uri.length() - _reqcfg->GetScope().length());
		docroot = _reqcfg->GetRoot();
	}
	path = docroot + uri;
	
	//isdir = _isDirectory(path);

	if (path.find(".") != std::string::npos)
	{
		std::string extension = path.substr(path.find_last_of("."), path.length() - path.find_last_of("."));
		if (_reqcfg && _reqcfg->GetCgi().size() != 0)
		{
			FOREACH_MAP_STR_CONST(_reqcfg->GetCgi(), cfgcgi){
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
		else{
			FOREACH_MAP_STR_CONST(_srvcfg->GetCgi(), cfgcgi){
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
	}
}

