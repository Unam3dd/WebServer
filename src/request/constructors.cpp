#include "http_request.hpp"
#include "http_utils.hpp"
#include "logger.hpp"
#include <iostream>

HttpRequest::HttpRequest(){}

HttpRequest::HttpRequest(const std::string& req, in_port_t port, char* ip):_ip(ip),_port(port)
{
	this->_badrequest = false;
	const char** http_headers = get_http_headers();
	for (int i = 0; http_headers[i]; i++)
		_header[http_headers[i]] = "";

	std::string line;
	t_status	status = STATUS_OK;

	if (req.length() == 0 || req.find("\r\n") == std::string::npos)
	{
		logz.logerr(L_ERROR | L_BYPASS, "Received Invalid Request (CRLF mandatory)");
		this->_badrequest = true;
		return ;
	}

	line = req.substr(0, req.find("\r\n"));
	status = _parseRequestLine(line);
	if (status != STATUS_OK)
	{
		logz.logerr(L_ERROR | L_BYPASS, "Error parsing request line: " + line);
		this->_badrequest = true;
		return ;
	}

	if (req.find("\r\n") == std::string::npos)
	{
		logz.logerr(L_ERROR | L_BYPASS, "Received Invalid Request (CRLF mandatory)");
		this->_badrequest = true;
		return ;
	}

	line = req.substr(req.find("\r\n") + 2, req.length() - req.find("\r\n"));
	status = _parseHeaders(line);
	if (status != STATUS_OK)
	{
		logz.logerr(L_ERROR | L_BYPASS, "Error parsing headers");
		this->_badrequest = true;
		return ;
	}
	if (req.find("\r\n\r\n") != std::string::npos && req.find("\r\n\r\n") + 4 < req.length())
		setBody(req.substr(req.find("\r\n\r\n") + 4, req.length() - req.find("\r\n\r\n")));
}
