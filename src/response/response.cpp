#include "http_response.hpp"

size_t	HttpResponse::writeResponse(const std::string &str)
{
	_body = str;
	return (_body.size());
}
