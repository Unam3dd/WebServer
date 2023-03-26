#include "http_request.hpp"
#include "http_utils.hpp"
#include "http_colors.hpp"
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
	if (line != "HTTP/1.0" && line != "HTTP/1.1")
		return (STATUS_FAIL);
	setVersion(line);
	
	return (STATUS_OK);
}

t_status	HttpRequest::_parseHeaders(const std::string &req)
{
	HttpRequest::t_parseMap callback;
	std::string buf = req;
	std::string key;
	std::string value;
	std::string line;
	std::string::size_type pos = 0;
	t_status err;

	for (line = buf.substr(0, buf.find("\r\n")); line != ""; line = buf.substr(0, buf.find("\r\n")))
	{
		buf = buf.substr(buf.find("\r\n") + 2, buf.length() - buf.find("\r\n"));
		pos = line.find(": ");
		if (pos == std::string::npos)
			return (STATUS_FAIL);
		key = line.substr(0, pos);
		LOWERCASE(key);
		value = line.substr(pos + 2, line.length());
		try{
			callback = _parseMap.at(key);
			err = (this->*callback)(value);
			if (err != STATUS_OK)
				return (err);
		}
		catch (std::exception &e)
		{
			std::cerr << WARN << "[HttpRequest::_parseHeaders] Received Invalid Header: " << key << RESET << std::endl;
		}
	}
	return (STATUS_OK);
}


