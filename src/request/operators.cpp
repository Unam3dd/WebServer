#include "http_request.hpp"
#include "http_utils.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const HttpRequest& req)
{
	os << "Method: " << req.getMethod() << std::endl;
	os << "Uri: " << req.getUri() << std::endl;
	os << "Version: " << req.getVersion() << std::endl;
	os << "Body: " << req.getBody() << std::endl;
	os << "Headers: " << std::endl;
	for (std::map<std::string, std::string>::const_iterator it = req.getHeaders().begin(); it != req.getHeaders().end(); ++it)
		os << "\t" << it->first << ": " << it->second << std::endl;
	return os;
}
