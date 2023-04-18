#include "http_request.hpp"
#include "http_utils.hpp"
#include <iostream>

void HttpRequest::setMethod(const std::string& method)
{
	if (method == "GET")
		_method = GET;
	else if (method == "POST")
		_method = POST;
	else if (method == "PUT")
		_method = PUT;
	else if (method == "DELETE")
		_method = DELETE;
	else
		_method = UNKNOWN;
}

void HttpRequest::setUri(const std::string& uri)
{
	_uri = uri;
}

void HttpRequest::setVersion(const std::string& version)
{
	_version = version;
}

void HttpRequest::setBody(const std::string &body)
{
	for (size_t i = 0; i < body.size(); i++)
		_body.push_back(body[i]);
	std::cout << "body size: " << _body.size() << std::endl;
}

void HttpRequest::setQueryString(const std::string &query_string)
{
	_querystring = query_string;
}
