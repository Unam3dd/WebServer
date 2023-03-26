#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <map>
#include "http_utils.hpp"

class HttpRequest
{
	public:
		HttpRequest(void);
		HttpRequest(const std::string& req);
		~HttpRequest(void);
	
	private:
		std::string	_method;
		std::string	_uri;
		std::string	_version;
		std::map<std::string, std::string> _header;
		std::string _body;
};

#endif
