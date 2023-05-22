/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:32:27 by stales            #+#    #+#             */
/*   Updated: 2023/05/22 22:57:25 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "http_utils.hpp"
#include "webserver.hpp"
#include <cstdlib>

bool	check_overflow_port(const std::string &str)
{
	if (str.empty()) return (false);

	unsigned long long	_ov = std::atoll(str.c_str());
	unsigned short		_real = _ov;

	return (_ov != _real);
}

WebServer*	SG_WebServer(const WebServer* ws)
{
	static WebServer*	_sg = NULL;

	if (ws)
		_sg = const_cast<WebServer*>(ws);
	return (_sg);
}

char**	SG_ENVP(char **envp){
	static char**	_sg = NULL;

	if (envp)
		_sg = envp;
	return (_sg);
}

std::string	SG_DefaultErrorPages(errpagecode_t status){
	if (status == E400)
		return ("<html><head><title>400 Bad Request</title></head><body><center><h1>400 Bad Request</h1></center></body></html>");
	if (status == E401)
		return ("<html><head><title>401 Unauthorized</title></head><body><center><h1>401 Unauthorized</h1></center></body></html>");
	if (status == E403)
		return ("<html><head><title>403 Forbidden</title></head><body><center><h1>403 Forbidden</h1></center></body></html>");
	if (status == E404)
		return ("<html><head><title>404 Not Found</title></head><body><center><h1>404 Not Found</h1></center></body></html>");
	if (status == E405)
		return ("<html><head><title>405 Method Not Allowed</title></head><body><center><h1>405 Method Not Allowed</h1></center></body></html>");
	if (status == E408)
		return ("<html><head><title>408 Request Timeout</title></head><body><center><h1>408 Request Timeout</h1></center></body></html>");
	if (status == E413)
		return ("<html><head><title>413 Request Entity Too Large</title></head><body><center><h1>413 Request Entity Too Large</h1></center></body></html>");
	if (status == E500)
		return ("<html><head><title>500 Internal Server Error</title></head><body><center><h1>500 Internal Server Error</h1></center></body></html>");
	if (status == E501)
		return ("<html><head><title>501 Not Implemented</title></head><body><center><h1>501 Not Implemented</h1></center></body></html>");
	if (status == E502)
		return ("<html><head><title>502 Bad Gateway</title></head><body><center><h1>502 Bad Gateway</h1></center></body></html>");
	if (status == E505)
		return ("<html><head><title>505 HTTP Version Not Supported</title></head><body><center><h1>505 HTTP Version Not Supported</h1></center></body></html>");
	return ("<h1>Fatal Server Error. Cannot Recover.</h1>");
}

std::string	SG_GetContentType(std::string& extension){
	extension = extension.substr(1);
	if (extension == "html" || extension == "htm")
		return ("text/html");
	if (extension == "css")
		return ("text/css");
	if (extension == "js")
		return ("text/javascript");
	if (extension == "png")
		return ("image/png");
	if (extension == "jpg" || extension == "jpeg")
		return ("image/jpeg");
	if (extension == "gif")
		return ("image/gif");
	if (extension == "svg")
		return ("image/svg+xml");
	if (extension == "ico")
		return ("image/x-icon");
	if (extension == "json")
		return ("application/json");
	if (extension == "pdf")
		return ("application/pdf");
	if (extension == "zip")
		return ("application/zip");
	if (extension == "xml")
		return ("application/xml");
	if (extension == "txt")
		return ("text/plain");
	if (extension == "mp3")
		return ("audio/mpeg");
	if (extension == "mp4")
		return ("video/mp4");
	if (extension == "mpeg")
		return ("video/mpeg");
	if (extension == "ogg")
		return ("video/ogg");
	if (extension == "webm")
		return ("video/webm");
	if (extension == "flv")
		return ("video/x-flv");
	if (extension == "avi")
		return ("video/x-msvideo");
	if (extension == "wmv")
		return ("video/x-ms-wmv");
	if (extension == "mpg")
		return ("video/x-mpeg");
	if (extension == "wav")
		return ("audio/x-wav");
	if (extension == "wma")
		return ("audio/x-ms-wma");
	if (extension == "flac")
		return ("audio/x-flac");
	if (extension == "aac")
		return ("audio/aac");
	if (extension == "m4a")
		return ("audio/x-m4a");
	if (extension == "m4v")
		return ("video/x-m4v");
	if (extension == "mov")
		return ("video/quicktime");
	if (extension == "qt")
		return ("video/quicktime");
	if (extension == "3gp")
		return ("video/3gpp");
	if (extension == "3g2")
		return ("video/3gpp2");
	if (extension == "3gpp")
		return ("video/3gpp");
	if (extension == "3gpp2")
		return ("video/3gpp2");
	if (extension == "mkv")
		return ("video/x-matroska");
	if (extension == "webp")
		return ("image/webp");
	if (extension == "woff")
		return ("font/woff");
	if (extension == "woff2")
		return ("font/woff2");
	if (extension == "ttf")
		return ("font/ttf");
	if (extension == "eot")
		return ("application/vnd.ms-fontobject");
	if (extension == "otf")
		return ("font/otf");
	if (extension == "sfnt")
		return ("application/font-sfnt");
	if (extension == "vtt")
		return ("text/vtt");
	if (extension == "csv")
		return ("text/csv");
	if (extension == "ics")
		return ("text/calendar");
	return ("text/html");
}
