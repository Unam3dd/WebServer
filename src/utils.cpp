/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:32:27 by stales            #+#    #+#             */
/*   Updated: 2023/05/24 19:43:45 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "http_utils.hpp"
#include "webserver.hpp"
#include <cstdlib>
#include <cstring>

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
	if (status == E411)
		return ("<html><head><title>411 Length Required</title></head><body><center><h1>411 Length Required</h1></center></body></html>");
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

static mime_content_type_t	*SG_mime_content_type(size_t *len)
{
	static mime_content_type_t	mimes[0x30] = {
		{ { "html", "htm"}, "text/html", 2},
		{ { "css" }, "text/css", 1},
		{ { "js" }, "text/javascript", 1},
		{ { "png" }, "image/png", 1},
		{ { "jpg", "jpeg" }, "image/jpeg", 1},
		{ { "gif" }, "image/gif", 1},
		{ { "svg" }, "image/svg+xml", 1},
		{ { "ico" }, "image/x-icon", 1},
		{ { "json"}, "application/json", 1},
		{ { "pdf" }, "application/pdf", 1},
		{ { "zip" }, "application/zip", 1},
		{ { "xml" }, "application/xml", 1},
		{ { "txt" }, "text/plain", 1},
		{ { "mp3" }, "audio/mpeg", 1},
		{ { "mp4" }, "video/mp4", 1},
		{ { "mpeg" }, "video/mpeg", 1},
		{ { "ogg" }, "video/ogg", 1},
		{ { "webm"}, "video/webm", 1},
		{ { "flv" }, "video/x-flv", 1},
		{ { "avi" }, "video/x-msvideo", 1},
		{ { "wmv" }, "video/x-ms-wmv", 1},
		{ { "mpg"}, "video/x-mpeg", 1},
		{ { "wav"}, "audio/x-wav", 1},
		{ { "wma"}, "audio-x-ms-wma", 1},
		{ { "flac"}, "audio/x-flac", 1},
		{ { "aac"}, "audio/aac", 1},
		{ { "m4a"}, "audio/x-m4a", 1},
		{ { "m4v"}, "audio/x-m4v", 1},
		{ { "mov"}, "video/quicktime", 1},
		{ { "qt"}, "video/quicktime", 1},
		{ { "3gp"}, "video/3gpp", 1},
		{ { "3g2"}, "video/3gpp2", 1},
		{ { "3gpp"}, "video/3gpp", 1},
		{ { "3gpp2"}, "video/3gpp2", 1},
		{ { "mkv"}, "video/x-matroska", 1},
		{ { "webp"}, "image/webp", 1},
		{ { "woff"}, "font/woff", 1},
		{ { "woff2"}, "font/woff2", 1},
		{ { "ttf"}, "font/ttf", 1},
		{ { "eot"}, "application/vnd.ms-fontobject", 1},
		{ { "otf"}, "font/otf", 1},
		{ { "sfnt"}, "application/font-sfnt", 1},
		{ { "vtt"}, "text/vtt", 1},
		{ { "csv"}, "text/csv", 1},
		{ { "ics"}, "text/calendar", 1}
	};

	if (len)
		*len = sizeof(mimes)/sizeof(mime_content_type_t);
	return (mimes);
}

std::string	SG_GetContentType(std::string& extension)
{
	size_t	len = 0;
	extension = extension.substr(1);
	mime_content_type_t	*m = SG_mime_content_type(&len);
	for (size_t i = 0; i < len; i++) {
		for (size_t j = 0; j < m[i].ext_len; j++)
			if (!std::strcmp(extension.c_str(), m[i].ext[j]))
				return (m[i].str);
	}
	return ("text/html");
}
