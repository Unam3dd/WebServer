#include "http_request.hpp"
#include "logger.hpp"
#include "http_utils.hpp"
#include <iostream>

static bool isHex(const std::string &str)
{
	for (int i = 0; i < (int)str.size(); i++){
		if (   (str[i] >= '0' && str[i] <= '9')
			|| (str[i] >= 'a' && str[i] <= 'f')
			|| (str[i] >= 'A' && str[i] <= 'F'))
			continue ;
		return (false);
	}
	return (true);
}

static char hexToChar(const std::string &str)
{
	return (char)(std::strtol(str.c_str(), NULL, 16));
}

t_status HttpRequest::_parseRequestLine(const std::string &reqline)
{
	std::string line = reqline;
	std::string method;
	std::string uri;
	std::string tmp;

	method = line.substr(0, line.find(" "));
	setMethod(method);

	line = line.substr(line.find(" ") + 1, line.length() - line.find(" "));
	uri = line.substr(0, line.find(" "));
	if (uri.length() == 0)
		return (STATUS_FAIL);
	for (int i = 0; i < (int)uri.length(); i++){
		if (uri[i] == '%')
		{
			tmp = &uri[i];
			logz.log(L_DEBUG, "Found URI-Encoded string at " + tmp);
			if (i + 2 >= (int)uri.length())
				return (STATUS_FAIL);
			tmp = uri.substr(i + 1, 2);
			if (!isHex(tmp))
				return (STATUS_FAIL);
			uri = uri.substr(0, i) + hexToChar(tmp) + uri.substr(i + 3, uri.length() - i - 3);
		} else if (uri[i] == '+'){
			uri[i] = ' ';
		} else
			uri[i] = uri[i];
	}

	if (uri.find("?") != std::string::npos)
	{
		setUri(uri.substr(0, uri.find("?")));
		setQueryString(uri.substr(uri.find("?") + 1, uri.length() - uri.find("?")));
	}
	else
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
			logz.logerr(L_WARN | L_BYPASS, "Header " + key + " does not exist");
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


