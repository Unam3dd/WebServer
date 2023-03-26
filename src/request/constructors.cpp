#include "http_request.hpp"
#include "http_utils.hpp"
#include "http_colors.hpp"
#include <iostream>

t_status HttpRequest::_parseRequestLine(const std::string &line)
{
	std::string method;
	std::string uri;
	std::string version;

	method = line.substr(0, line.find(" "));
	if (method == "GET" || method == "POST" || method == "PUT" || method == "DELETE")
		setMethod(method);
	else
		return (STATUS_FAIL);

	line.substr(line.find(" "), line.length());
	uri = line.substr(0, line.find(" "));
	if (uri.length() != 0)
		setUri(uri);
	else
		return (STATUS_FAIL);

	line.substr(line.find(" "), line.length());
	if (line != "HTTP/1.0" || line != "HTTP/1.1")
		return (STATUS_FAIL);
	setVersion(version);
	return (STATUS_OK);
}

HttpRequest::HttpRequest(const std::string& req)
{
	std::string line;
	t_status	status = STATUS_OK;

	line = req.substr(0, req.find("\r\n"));
	status = _parseRequestLine(line);
	if (status != STATUS_OK)
		std::cerr << FAIL << "[HttpRequest::HttpRequest] Error parsing request line" << std::endl;
}
