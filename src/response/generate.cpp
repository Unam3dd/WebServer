/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:02:59 by ldournoi          #+#    #+#             */
/*   Updated: 2023/04/18 18:06:39 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_response.hpp"
#include "http_status.hpp"
#include "http_utils.hpp"
#include "utils.hpp"

/* *
 * @brief: generate the full http response from the response object. at this 
 * point, the response object should have all the necessary information to
 * generate the response, populated by _prepareXXXresponse() functions.
 *
 * @param: none
 * @return: none
 *
 */
void HttpResponse::_generateResponse(void){
	time_t now = time(NULL);
	struct tm *t = gmtime(&now);
	char buf[0x100];
	strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S %Z", t);

	this->_fullresponse += "HTTP/1.1 " + NumberToString(_status) + " " + get_http_status_msg(_status) + "\r\n";
	this->_fullresponse += "Server: WebServ " + std::string(VERSION) + "\r\n";
	this->_fullresponse += "Date: " + std::string(buf) + "\r\n";
	_contenttype != "" ? this->_fullresponse += "Content-Type: " + this->_contenttype + "\r\n" : "";
	_body.size() != 0  ? this->_fullresponse += "Content-Length: " + NumberToString(this->_body.size()) + "\r\n" : "";
	this->_fullresponse += "Connection: close\r\n";
	this->_fullresponse += "\r\n";
	this->_fullresponse += this->_body;
}

void	HttpResponse::_generateResponseCgi(void){
	std::string status;
	std::string cgiresponse = _cgibuf.data();

	if (cgiresponse.size() == 0)
	{
		_status = HTTP_STATUS_INTERNAL_SERVER_ERROR;
		_body = _getErrorPageContent(_status);
		_contenttype = "text/html";
		_generateResponse();
		return;
	}
	if (cgiresponse.find("Status: ") == std::string::npos && cgiresponse.find("status: ") == std::string::npos)
		_status = HTTP_STATUS_OK;
	else{
		status = cgiresponse.substr(cgiresponse.find("Status: ") + 8, cgiresponse.length() - cgiresponse.find("Status: "));
		status = status.substr(0, status.find("\r\n"));
		this->_status = SANITIZE_AND_CAST_INT_TO_HTTP_STATUS(std::atoi(status.c_str()));
		}
	this->_fullresponse += "HTTP/1.1 " + NumberToString(_status) + " " + get_http_status_msg(_status) + "\r\n";
	this->_fullresponse += static_cast<std::string>(this->_cgibuf.data());
}
