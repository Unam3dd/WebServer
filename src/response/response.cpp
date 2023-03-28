#include "http_response.hpp"

size_t	HttpResponse::writeResponse(const std::string &str)
{
	if (_body.capacity() < str.capacity())
		_body.reserve(str.capacity());
	//_body.copy(const_cast<char*>(str.c_str()), str.size());
	_body = str;
	return (_body.size());
}
