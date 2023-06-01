#include "http_request.hpp"
#include "http_utils.hpp"
#include "logger.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const HttpRequest& req)
{
	if (req.isBadRequest())
	{
		os << ANSI_FMT(R, "bad request");
		return os;
	}
	os << "\n\tMethod: " << STR_METHOD(req.getMethod()) << std::endl;
	os << "\tUri: " << req.getUri() << std::endl;
	os << "\tVersion: " << req.getVersion() << std::endl;
	os << "\tHeaders: " << std::endl;
	for (std::map<std::string, std::string>::const_iterator it = req.getHeaders().begin(); it != req.getHeaders().end(); ++it)
		if (it->second != "")
			os << "\t\t" << it->first << ": " << it->second << std::endl;
	os << "\tBody: " << std::endl << req.getBody().data() << std::endl;
	return os;
}
