#include "http_request.hpp"
#include "http_utils.hpp"

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
	_body = body;
}
