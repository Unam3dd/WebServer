#include "http_request.hpp"
#include "http_utils.hpp"
#include "http_colors.hpp"
#include <iostream>

HttpRequest::HttpRequest(const std::string& req)
{
	std::string line;
	t_status	status = STATUS_OK;

	line = req.substr(0, req.find("\r\n"));
	status = _parseRequestLine(line);
	if (status != STATUS_OK)
		std::cerr << FAIL << "[HttpRequest::HttpRequest] Error parsing request line" << std::endl;
	
	line = req.substr(req.find("\r\n") + 2, req.length() - req.find("\r\n"));
	status = _parseHeaders(line);
	if (status != STATUS_OK)
		std::cerr << FAIL << "[HttpRequest::HttpRequest] Error parsing headers" << std::endl;
	
	setBody(req.substr(req.find("\r\n\r\n") + 4, req.length() - req.find("\r\n\r\n")));
}
