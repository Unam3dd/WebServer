/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:57:36 by ldournoi          #+#    #+#             */
/*   Updated: 2023/03/18 16:31:44 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config.hpp"
#include "http_colors.hpp"
#include "http_utils.hpp"
#include "utils.hpp"
#include "webserver.hpp"
#include <cstdlib>
#include <iostream>

t_errcode	HttpServerConfig::SetServerNames(const std::vector<std::string> &names)
{
	(void)names;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetServerNames] setting server names" << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetIndexes(const std::vector<std::string> &indexs)
{
	(void)indexs;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetIndexes] setting indexes" << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetServerPorts(const std::vector<std::string> &ports)
{
	(void)ports;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetServerPorts] setting server ports" << std::endl;
	/*
	int port = 0;
	for (std::vector<std::string>::const_iterator it = ports.begin(); it != ports.end(); it++)
	{
		if (check_overflow_port(*it))
			return (ERRPARSE_PORT);
		port = std::atoi(it->c_str());
		if (port <= 0 || port > 65535)
			return (ERRPARSE_PORT);
		this->_ports.push_back(static_cast<port_t>(port));
	}
	*/
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetErrorPages(const std::vector<std::string> &pages)
{
	(void)pages;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetErrorPages] setting error pages" << std::endl;
	return (ERRPARSE_OK);
	/*
	if (pages.at(0) == "errpage400")
	{
		this->_errpages[E400].code = 400;
		this->_errpages[E400].path = pages.at(1);
	}
	else if (pages.at(0) == "errpage401")
	{
		this->_errpages[E401].code = 401;
		this->_errpages[E401].path = pages.at(1);
	}
	else if (pages.at(0) == "errpage403")
	{
		this->_errpages[E403].code = 403;
		this->_errpages[E403].path = pages.at(1);
	}
	else if (pages.at(0) == "errpage404")
	{
		this->_errpages[E404].code = 404;
		this->_errpages[E404].path = pages.at(1);
	}
	else if (pages.at(0) == "errpage405")
	{
		this->_errpages[E405].code = 405;
		this->_errpages[E405].path = pages.at(1);
	}
	else if (pages.at(0) == "errpage500")
	{
		this->_errpages[E500].code = 500;
		this->_errpages[E500].path = pages.at(1);
	}
	else if (pages.at(0) == "errpage501")
	{
		this->_errpages[E501].code = 501;
		this->_errpages[E501].path = pages.at(1);
	}
	else if (pages.at(0) == "errpage505")
	{
		this->_errpages[E505].code = 505;
		this->_errpages[E505].path = pages.at(1);
	}
	return (ERRPARSE_ERRPAGE);
	*/
}

t_errcode	HttpServerConfig::SetRoot(const std::vector<std::string> &root)
{
	(void)root;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetRoot] setting root" << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetMaxPostSize(const std::vector<std::string> &max_size_post)
{
	(void)max_size_post;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetMaxPostSize] setting max post size" << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetSessionPath(const std::vector<std::string> &sessionpath)
{
	(void)sessionpath;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetSessionPath] setting session path" << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetServerTimeout(const std::vector<std::string> &sessiontimeout)
{
	(void)sessiontimeout;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetServerTimeout] setting session timeout" << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetCookies(const std::vector<std::string> &cookies)
{
	(void)cookies;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetCookies] setting cookies" << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetUploads(const std::vector<std::string> &uploads)
{
	(void)uploads;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetUploads] setting uploads" << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetDirList(const std::vector<std::string> &dirlist)
{
	(void)dirlist;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetDirList] setting dir list" << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetCgi(const std::vector<std::string> &cgi)
{
	(void)cgi;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetCgi] setting cgi" << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetMethods(const std::vector<std::string> &methods)
{
	(void)methods;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetMethods] setting methods" << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetUploadDir(const std::vector<std::string> &uploaddir)
{
	(void)uploaddir;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetUploadDir] setting upload dir" << std::endl;
	return (ERRPARSE_OK);
}
