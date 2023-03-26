#include "http_request.hpp"

void HttpRequest::setMethod(const std::string& method)
{
	methods_t m = getMethod();

	if (method == "GET")
		m = GET;
	else if (method == "POST")
		m = POST;
	else if (method == "PUT")
		m = PUT;
	else if (method == "DELETE")
		m = DELETE;
	_method = m;
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
