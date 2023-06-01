#include "webserver.hpp"
#include "utils.hpp"

unsigned long long	WebServer::_checkContentLength(const std::string& buffer)
{
	std::string	headers;
	
	headers = buffer.substr(0, buffer.find("\r\n\r\n"));
	LOWERCASE(headers);
	if (headers.find("content-length:") == std::string::npos)
		return (-1);

	std::string	content_length;
	size_t		pos;
	size_t		pos2;

	pos = headers.find("content-length:");
	pos2 = headers.find("\r\n", pos);
	content_length = headers.substr(pos + 15, pos2 - pos - 15);
	if (content_length.find_first_not_of("0123456789") != std::string::npos)
		return (-1);

	return (StringToNumber<unsigned long long>(content_length));
}
