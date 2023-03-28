#include "http_request.hpp"
#include "http_utils.hpp"
#include "http_colors.hpp"
#include <iostream>

const char**	get_http_headers()
{
	static const char* http_headers[] = {
		"accept",
		"accept-charset",
		"accept-encoding",
		"accept-language",
		"accept-ranges",
		"age",
		"allow",
		"authorization",
		"cache-control",
		"connection",
		"content-encoding",
		"content-language",
		"content-length",
		"content-location",
		"content-md5",
		"content-range",
		"content-type",
		"cookie",
		"date",
		"etag",
		"expect",
		"expires",
		"from",
		"host",
		"if-match",
		"if-modified-since",
		"if-none-match",
		"if-range",
		"if-unmodified-since",
		"last-modified",
		"location",
		"max-forwards",
		"pragma",
		"proxy-authenticate",
		"proxy-authorization",
		"range",
		"referer",
		"retry-after",
		"server",
		"te",
		"trailer",
		"transfer-encoding",
		"upgrade",
		"user-agent",
		"vary",
		"via",
		"warning",
		"www-authenticate",
		NULL
	};
	
	return (http_headers);
}


HttpRequest::HttpRequest(const std::string& req, in_port_t port): _port(port)
{
	const char** http_headers = get_http_headers();
	for (int i = 0; http_headers[i]; i++)
		_header[http_headers[i]] = "";
	
	std::string line;
	t_status	status = STATUS_OK;

	if (req.length() == 0 || req.find("\r\n") == std::string::npos)
	{
		std::cerr << FAIL << "[HttpRequest::HttpRequest] Received Invalid Request (CRLF mandatory)" << RESET << std::endl;
		return ;
	}

	line = req.substr(0, req.find("\r\n"));
	status = _parseRequestLine(line);
	if (status != STATUS_OK)
	{
		std::cerr << FAIL << "[HttpRequest::HttpRequest] Error parsing request line" << std::endl;
		return ;
	}
	
	line = req.substr(req.find("\r\n") + 2, req.length() - req.find("\r\n"));
	status = _parseHeaders(line);
	if (status != STATUS_OK)
	{
		std::cerr << FAIL << "[HttpRequest::HttpRequest] Error parsing headers" << std::endl;
		return ;
	}
	
	setBody(req.substr(req.find("\r\n\r\n") + 4, req.length() - req.find("\r\n\r\n")));

}
