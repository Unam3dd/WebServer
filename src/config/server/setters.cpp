/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:57:36 by ldournoi          #+#    #+#             */
/*   Updated: 2023/03/20 02:03:18 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config.hpp"
#include "http_colors.hpp"
#include "http_utils.hpp"
#include "utils.hpp"
#include "webserver.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <cmath>

t_errcode	HttpServerConfig::SetServerNames(const std::vector<std::string> &names)
{
	static bool	already_set = false;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetServerNames] setting server names" << std::endl;
	if (already_set)
		return (ERRPARSE_DUP);
	for (size_t i = 1; i < names.size(); i++)
	{
		if (names.at(i).find_first_of(" \t") != std::string::npos)
			return (ERRPARSE_SPCORTAB);
		this->_names.push_back(names.at(i));
		if (DEBUG)
			std::cout << DBG << "[HttpServerConfig::SetServerNames] pushed server_name[" << i - 1<< "]: " << _names.at(i - 1) << std::endl;
		already_set = true;
	}
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetIndexes(const std::vector<std::string> &indexs)
{
	static bool	already_set = false;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetIndexes] setting indexes" << std::endl;
	if (already_set)
		return (ERRPARSE_DUP);
	for (size_t i = 1; i < indexs.size(); i++)
	{
		if (indexs.at(i).find_first_of(" \t") != std::string::npos)
			return (ERRPARSE_SPCORTAB);
		this->_indexs.push_back(indexs.at(i));
		if (DEBUG)
			std::cout << DBG << "[HttpServerConfig::SetIndexes] pushed index[" << i - 1<< "]: " << _indexs.at(i - 1) << std::endl;
		already_set = true;
	}
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetServerPorts(const std::vector<std::string> &ports)
{
	static bool	already_set = false;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetServerPorts] setting server ports" << std::endl;
	if (already_set)
		return (ERRPARSE_DUP);
	int port = 0;
	for (size_t i = 1; i < ports.size(); i++)
	{
		if (check_overflow_port(ports.at(i)))
			return (ERRPARSE_PORT);
		port = std::atoi(ports.at(i).c_str());
		if (port <= 0 || port > 65535)
			return (ERRPARSE_PORT);
		this->_ports.push_back(static_cast<port_t>(port));
		if (DEBUG)
			std::cout << DBG << "[HttpServerConfig::SetServerPorts] pushed port[" << i - 1<< "]: " << _ports.at(i - 1) << std::endl;
		already_set = true;
	}
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetErrorPages(const std::vector<std::string> &pages)
{
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetErrorPages] setting error pages" << std::endl;
	if (pages.size() != 3)
		return (ERRPARSE_ERRPAGE);
	if (pages.at(1) == "400")
	{
		if (DEBUG)
			std::cout << DBG << "[HttpServerConfig::SetErrorPages] setting error page 400 to:" << pages.at(2) << std::endl;
		this->_errpages[E400].path = pages.at(2);
	}
	else if (pages.at(1) == "401")
	{
		if (DEBUG)
			std::cout << DBG << "[HttpServerConfig::SetErrorPages] setting error page 401 to:" << pages.at(2) << std::endl;
		this->_errpages[E401].path = pages.at(2);
	}
	else if (pages.at(1) == "403")
	{
		if (DEBUG)
			std::cout << DBG << "[HttpServerConfig::SetErrorPages] setting error page 403 to:" << pages.at(2) << std::endl;
		this->_errpages[E403].path = pages.at(2);
	}
	else if (pages.at(1) == "404")
	{
		if (DEBUG)
			std::cout << DBG << "[HttpServerConfig::SetErrorPages] setting error page 404 to:" << pages.at(2) << std::endl;
		this->_errpages[E404].path = pages.at(2);
	}
	else if (pages.at(1) == "405")
	{
		if (DEBUG)
			std::cout << DBG << "[HttpServerConfig::SetErrorPages] setting error page 405 to:" << pages.at(2) << std::endl;
		this->_errpages[E405].path = pages.at(2);
	}
	else if (pages.at(1) == "500")
	{
		if (DEBUG)
			std::cout << DBG << "[HttpServerConfig::SetErrorPages] setting error page 500 to:" << pages.at(2) << std::endl;
		this->_errpages[E500].path = pages.at(2);
	}
	else if (pages.at(1) == "501")
	{
		if (DEBUG)
			std::cout << DBG << "[HttpServerConfig::SetErrorPages] setting error page 501 to:" << pages.at(2) << std::endl;
		this->_errpages[E501].path = pages.at(2);
	}
	else if (pages.at(1) == "505")
	{
		if (DEBUG)
			std::cout << DBG << "[HttpServerConfig::SetErrorPages] setting error page 505 to:" << pages.at(2) << std::endl;
		this->_errpages[E505].path = pages.at(2);
	}
	else
		return (ERRPARSE_ERRPAGE);
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetRoot(const std::vector<std::string> &root)
{
	static bool	already_set = false;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetRoot] setting root" << std::endl;
	if (already_set)
		return (ERRPARSE_DUP);
	this->_root = root.at(1);
	if (this->_root.at(this->_root.size() - 1) != '/')
		this->_root += '/';
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetRoot] root set to: " << this->GetRoot() << _root << std::endl;
	already_set = true;
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetMaxPostSize(const std::vector<std::string> &max_size_post)
{
	static bool	already_set = false;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetMaxPostSize] setting max post size" << std::endl;
	if (already_set)
		return (ERRPARSE_DUP);
	if (std::atof(max_size_post.at(1).c_str()) < 0 || std::atof(max_size_post.at(1).c_str()) == HUGE_VAL)
		return (ERRPARSE_POST);
	this->_max_size_post = std::atof(max_size_post.at(1).c_str());
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetMaxPostSize] max post size set to: " << this->GetMaxPostSize() << std::endl;
	already_set = true;
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetSessionPath(const std::vector<std::string> &sessionpath)
{
	static bool	already_set = false;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetSessionPath] setting session path" << std::endl;
	if (already_set)
		return (ERRPARSE_DUP);
	this->_sessionpath = sessionpath.at(1);
	if (this->_sessionpath.at(this->_sessionpath.size() - 1) != '/')
		this->_sessionpath += '/';
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetSessionPath] session path set to: " << this->GetSessionPath() << std::endl;
	already_set = true;
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetServerTimeout(const std::vector<std::string> &sessiontimeout)
{
	static bool	already_set = false;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetServerTimeout] setting session timeout" << std::endl;
	if (already_set)
		return (ERRPARSE_DUP);
	if (std::atof(sessiontimeout.at(1).c_str()) < 0 || std::atof(sessiontimeout.at(1).c_str()) > 3600)
		return (ERRPARSE_TIMEOUT);
	this->_timeout = std::atof(sessiontimeout.at(1).c_str());
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetServerTimeout] session timeout set to: " << this->GetServerTimeout() << std::endl;
	already_set = true;
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetCookies(const std::vector<std::string> &cookies)
{
	static bool	already_set = false;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetCookies] setting cookies" << std::endl;
	if (already_set)
		return (ERRPARSE_DUP);
	std::string tmp = cookies.at(1);
	LOWERCASE(tmp);
	if (tmp == "on")
		this->_cookies = true;
	else if (tmp == "off")
		this->_cookies = false;
	else
		return (ERRPARSE_COOKIES);
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetCookies] cookies set to: " << this->GetCookies() << std::endl;
	already_set = true;
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetUploads(const std::vector<std::string> &uploads)
{
	static bool	already_set = false;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetUploads] setting uploads" << std::endl;
	if (already_set)
		return (ERRPARSE_DUP);
	std::string tmp = uploads.at(1);
	LOWERCASE(tmp);
	if (tmp == "on")
		this->_uploads = true;
	else if (tmp == "off")
		this->_uploads = false;
	else
		return (ERRPARSE_UPLOADS);
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetUploads] uploads set to: " << this->GetUploads() << std::endl;
	already_set = true;
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetDirList(const std::vector<std::string> &dirlist)
{
	static bool	already_set = false;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetDirList] setting dir list" << std::endl;
	if (already_set)
		return (ERRPARSE_DUP);
	std::string tmp = dirlist.at(1);
	LOWERCASE(tmp);
	if (tmp == "on")
		this->_dirlist = true;
	else if (tmp == "off")
		this->_dirlist = false;
	else
		return (ERRPARSE_DIRLIST);
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetDirList] dir list set to: " << this->GetDirList() << std::endl;
	already_set = true;
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetCgi(const std::vector<std::string> &cgi)
{
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetCgi] setting cgi" << std::endl;
	if (cgi.size() < 3)
		return (ERRPARSE_CGI);
	try{
		this->_cgi.at(cgi.at(1));
		return (ERRPARSE_DUP);
	}
	catch (std::out_of_range &e)
	{
		(void)e;
	}
	this->_cgi[cgi.at(1)] = cgi.at(2);
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetCgi] cgi: " << cgi.at(1) << " -> " << this->_cgi[cgi.at(1)] << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetMethods(const std::vector<std::string> &methods)
{
	static bool	already_set = false;
	int	tmp;
	std::string tmpstr;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetMethods] setting methods" << std::endl;
	if (already_set)
		return (ERRPARSE_DUP);
	for (size_t i = 1; i < methods.size(); i++)
	{
		tmpstr = methods.at(i);
		LOWERCASE(tmpstr);
		if (tmpstr == "get")
			tmp = tmp | GET;
		else if (tmpstr == "post")
			tmp = tmp | POST;
		else if (tmpstr == "put")
			tmp = tmp | PUT;
		else if (tmpstr == "delete")
			tmp = tmp | DELETE;
		else
			return (ERRPARSE_METHODS);
	}
	this->_methods = static_cast<methods_t>(tmp);
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetMethods] methods set to: " << this->GetMethods() << std::endl;
	already_set = true;
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetUploadDir(const std::vector<std::string> &uploaddir)
{
	static bool	already_set = false;
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetUploadDir] setting upload dir" << std::endl;
	if (already_set)
		return (ERRPARSE_DUP);
	this->_uploaddir = uploaddir.at(1);
	if (DEBUG)
		std::cout << DBG << "[HttpServerConfig::SetUploadDir] upload dir set to: " << this->GetUploadDir() << std::endl;
	already_set = true;
	return (ERRPARSE_OK);
}
