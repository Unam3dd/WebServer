#include "http_client.hpp"
#include "http_status.hpp"
#include <netinet/in.h>
#include <sstream>
#include <iostream>

http_status_code_t	HttpClient::get(const std::string& url)
{
	if (url.empty()) return (HTTP_STATUS_BAD_REQUEST);

	ParseURL	p(url);

	RequestFormatter	fmt(p, GET);

	return (this->_status);
}
