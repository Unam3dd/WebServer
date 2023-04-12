#include "http_response.hpp"
#include <iostream>

std::string	HttpResponse::_getQuery(void)
{
	std::string	str = this->_request.getUri();
	size_t		pos = 0;

	pos = str.find("?");
	return ((pos != std::string::npos) ?
			str.substr(pos+1, str.size() - pos+1)
			: "");
}
