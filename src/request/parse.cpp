#include "http_request.hpp"
#include "http_colors.hpp"
#include "http_utils.hpp"
#include <iostream>

t_status HttpRequest::_parseRequestLine(const std::string &reqline)
{
	std::string line = reqline;
	std::string method;
	std::string uri;

	method = line.substr(0, line.find(" "));
	if (method != "GET" && method != "POST" && method != "PUT" && method != "DELETE")
		return (STATUS_FAIL);
	setMethod(method);

	line = line.substr(line.find(" ") + 1, line.length() - line.find(" "));
	uri = line.substr(0, line.find(" "));
	if (uri.length() == 0)
		return (STATUS_FAIL);
	setUri(uri);

	line = line.substr(line.find(" ") + 1, line.length() - line.find(" "));
	setVersion(line);
	
	return (STATUS_OK);
}

t_status	HttpRequest::_parseHeaders(const std::string &req)
{
	std::string buf = req;
	std::string key;
	std::string value;
	std::string line;
	std::string::size_type pos = 0;

	for (line = buf.substr(0, buf.find("\r\n")); line != ""; line = buf.substr(0, buf.find("\r\n")))
	{
		buf = buf.substr(buf.find("\r\n") + 2, buf.length() - buf.find("\r\n"));
		pos = line.find(": ");
		if (pos == std::string::npos)
			return (STATUS_FAIL);
		key = line.substr(0, pos);
		LOWERCASE(key);
		value = line.substr(pos + 2, line.length());
		if (_header.find(key) == _header.end())
		{
			std::cerr << WARN << "[HttpRequest::_parseHeaders] Header " << key << " does not exist" << std::endl;
			continue ;
		}
		if (key == "host")
			_header[key] = value.substr(0, value.find(":"));
		else
			_header[key] = value;
		if (buf.find("\r\n") == std::string::npos)
			break;
	}
	return (STATUS_OK);
}


