/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:57:36 by ldournoi          #+#    #+#             */
/*   Updated: 2023/05/24 17:18:32 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config.hpp"
#include "logger.hpp"
#include "http_utils.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <cmath>

t_errcode	HttpServerConfig::SetServerNames(const std::vector<std::string> &names)
{
	logz.log(L_DEBUG, "setting server names");
	for (size_t i = 1; i < names.size(); i++)
	{
		if (names.at(i).find_first_of(" \t") != std::string::npos)
			return (ERRPARSE_SPCORTAB);
		this->_names.push_back(names.at(i));
		logz.log(L_DEBUG, "pushed server_name[" + logz.itoa(i - 1) + "]: " + _names.at(i - 1));
	}
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetIndexes(const std::vector<std::string> &indexs)
{
	logz.log(L_DEBUG, "setting indexes");
	for (size_t i = 1; i < indexs.size(); i++)
	{
		if (indexs.at(i).find_first_of(" \t") != std::string::npos)
			return (ERRPARSE_SPCORTAB);
		this->_indexs.push_back(indexs.at(i));
		logz.log(L_DEBUG, "pushed index[" + logz.itoa(i - 1) + "]: " + _indexs.at(i - 1));
	}
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetServerPorts(const std::vector<std::string> &ports)
{
	int port = 0;

	logz.log(L_DEBUG, "setting server ports");
	for (size_t i = 1; i < ports.size(); i++)
	{
		if (check_overflow_port(ports.at(i)))
			return (ERRPARSE_PORT);
		port = std::atoi(ports.at(i).c_str());
		if (port <= 0 || port > 0xFFFF) return (ERRPARSE_PORT);
		this->_ports.push_back(static_cast<port_t>(port));
		logz.log(L_DEBUG, "pushed port[" + logz.itoa(i - 1) + "]: " +logz.itoa(_ports.at(i - 1)));
	}
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetErrorPages(const std::vector<std::string> &pages)
{
	logz.log(L_DEBUG, "setting error pages");
	if (pages.size() != 3)
		return (ERRPARSE_ERRPAGE);
	if (pages.at(1) == "400")
	{
		logz.log(L_DEBUG, "setting error page 400 to: " + pages.at(2));
		this->_errpages[E400].path = pages.at(2);
	}
	else if (pages.at(1) == "401")
	{
		logz.log(L_DEBUG, "setting error page 401 to: " + pages.at(2));
		this->_errpages[E401].path = pages.at(2);
	}
	else if (pages.at(1) == "403")
	{
		logz.log(L_DEBUG, "setting error page 403 to: " + pages.at(2));
		this->_errpages[E403].path = pages.at(2);
	}
	else if (pages.at(1) == "404")
	{
		logz.log(L_DEBUG, "setting error page 404 to: " + pages.at(2));
		this->_errpages[E404].path = pages.at(2);
	}
	else if (pages.at(1) == "405")
	{
		logz.log(L_DEBUG, "setting error page 405 to: " + pages.at(2));
		this->_errpages[E405].path = pages.at(2);
	}
	else if (pages.at(1) == "500")
	{
		logz.log(L_DEBUG, "setting error page 500 to: " + pages.at(2));
		this->_errpages[E500].path = pages.at(2);
	}
	else if (pages.at(1) == "501")
	{
		logz.log(L_DEBUG, "setting error page 501 to: " + pages.at(2));
		this->_errpages[E501].path = pages.at(2);
	}
	else if (pages.at(1) == "505")
	{
		logz.log(L_DEBUG, "setting error page 505 to: " + pages.at(2));
		this->_errpages[E505].path = pages.at(2);
	}
	else
		return (ERRPARSE_ERRPAGE);
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetRoot(const std::vector<std::string> &root)
{
	logz.log(L_DEBUG, "setting root");
	if (root.size() != 2)
		return (ERRPARSE_NBARGS);
	this->_root = root.at(1);
	if (this->_root.at(this->_root.size() - 1) != '/')
		this->_root += '/';
	logz.log(L_DEBUG, "root set to: " + this->GetRoot());
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetMaxPostSize(const std::vector<std::string> &max_size_post)
{
	std::string tmp = max_size_post.at(1);

	logz.log(L_DEBUG, "setting max post size");
	if (max_size_post.size() != 2 && (std::atof(tmp.c_str()) < 0 || std::atof(tmp.c_str()) == HUGE_VAL))
		return (ERRPARSE_POST);
	maxpost_size_t max_size = std::atof(tmp.c_str());
	if (tmp.find_first_not_of("0123456789") != std::string::npos)
	{
		if (tmp.find_first_not_of("0123456789") != tmp.size() - 1)
			return (ERRPARSE_POST);
		LOWERCASE(tmp);
		switch (tmp.at(tmp.size() - 1))
		{
			case 'k':
				max_size *= 1024;
				break;
			case 'm':
				max_size *= 1024 * 1024;
				break;
			case 'g':
				max_size *= 1024 * 1024 * 1024;
				break;
			default:
				return (ERRPARSE_POST);
		}
	}

	this->_max_size_post = max_size;
	logz.log(L_DEBUG, "max post size set to: (in bytes): " + logz.itoa(this->GetMaxPostSize()));
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetCookies(const std::vector<std::string> &cookies)
{
	logz.log(L_DEBUG, "setting cookies");
	std::string tmp = cookies.at(1);
	LOWERCASE(tmp);
	if (tmp == "on")
		this->_cookies = true;
	else if (tmp == "off")
		this->_cookies = false;
	else
		return (ERRPARSE_COOKIES);
	logz.log(L_DEBUG, "cookies set to: " + logz.boolean(this->GetCookies()));
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetUploads(const std::vector<std::string> &uploads)
{
	logz.log(L_DEBUG, "setting uploads");
	std::string tmp = uploads.at(1);
	LOWERCASE(tmp);
	if (tmp == "on")
		this->_uploads = true;
	else if (tmp == "off")
		this->_uploads = false;
	else
		return (ERRPARSE_UPLOADS);
	logz.log(L_DEBUG, "uploads set to: " + logz.boolean(this->GetUploads()));
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetDirList(const std::vector<std::string> &dirlist)
{
	logz.log(L_DEBUG, "setting dir list");
	std::string tmp = dirlist.at(1);
	LOWERCASE(tmp);
	if (tmp == "on")
		this->_dirlist = true;
	else if (tmp == "off")
		this->_dirlist = false;
	else
		return (ERRPARSE_DIRLIST);
	logz.log(L_DEBUG, "dir list set to: " + logz.boolean(this->GetDirList()));
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetCgi(const std::vector<std::string> &cgi)
{
	logz.log(L_DEBUG, "setting cgi");
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
	logz.log(L_DEBUG, "cgi: " + cgi.at(1) + " -> " + this->_cgi[cgi.at(1)]);
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetMethods(const std::vector<std::string> &methods)
{
	int	tmp = 0;
	std::string tmpstr;
	logz.log(L_DEBUG, "setting methods");
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
	logz.log(L_DEBUG, "methods set to: " + logz.get_methods(this->GetMethods()));
	return (ERRPARSE_OK);
}
