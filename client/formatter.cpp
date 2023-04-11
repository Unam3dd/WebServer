#include "http_client.hpp"
#include <iostream>

RequestFormatter::RequestFormatter(void)
{
}

RequestFormatter::RequestFormatter(ParseURL& url, http_method_t method)
{
	(void)url;
	std::cout << get_string_method(method) << std::endl;
}

RequestFormatter::~RequestFormatter(void)
{
}

const char	*RequestFormatter::get_string_method(http_method_t method)
{
	static const char	*str[4] = {
		"GET",
		"POST",
		"PUT",
		"DELETE"
	};

	return (str[method]);
}
