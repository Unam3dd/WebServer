/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:59:57 by ldournoi          #+#    #+#             */
/*   Updated: 2023/03/29 21:19:15 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_request_config.hpp"
#include "http_colors.hpp"
#include "http_utils.hpp"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>

t_errcode	HttpRequestConfig::SetIndexes(const std::vector<std::string> &indexs)
{
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetIndexes] setting indexes" << std::endl;
	for (size_t i = 1; i < indexs.size(); i++)
	{
		if (indexs.at(i).find_first_of(" \t") != std::string::npos)
			return (ERRPARSE_SPCORTAB);
		this->_indexs.push_back(indexs.at(i));
		if (DEBUG)
			std::cout << DBG << "[HttpRequestConfig::SetIndexes] pushed index[" << i - 1<< "]: " << _indexs.at(i - 1) << std::endl;
	}
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetErrorPages(const std::vector<std::string> &pages)
{
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetErrorPages] setting error pages" << std::endl;
	if (pages.size() != 3)
		return (ERRPARSE_ERRPAGE);
	if (pages.at(1) == "400")
	{
		if (DEBUG)
			std::cout << DBG << "[HttpRequestConfig::SetErrorPages] setting error page 400 to:" << pages.at(2) << std::endl;
		this->_errpages[E400].path = pages.at(2);
	}
	else if (pages.at(1) == "401")
	{
		if (DEBUG)
			std::cout << DBG << "[HttpRequestConfig::SetErrorPages] setting error page 401 to:" << pages.at(2) << std::endl;
		this->_errpages[E401].path = pages.at(2);
	}
	else if (pages.at(1) == "403")
	{
		if (DEBUG)
			std::cout << DBG << "[HttpRequestConfig::SetErrorPages] setting error page 403 to:" << pages.at(2) << std::endl;
		this->_errpages[E403].path = pages.at(2);
	}
	else if (pages.at(1) == "404")
	{
		if (DEBUG)
			std::cout << DBG << "[HttpRequestConfig::SetErrorPages] setting error page 404 to:" << pages.at(2) << std::endl;
		this->_errpages[E404].path = pages.at(2);
	}
	else if (pages.at(1) == "405")
	{
		if (DEBUG)
			std::cout << DBG << "[HttpRequestConfig::SetErrorPages] setting error page 405 to:" << pages.at(2) << std::endl;
		this->_errpages[E405].path = pages.at(2);
	}
	else if (pages.at(1) == "500")
	{
		if (DEBUG)
			std::cout << DBG << "[HttpRequestConfig::SetErrorPages] setting error page 500 to:" << pages.at(2) << std::endl;
		this->_errpages[E500].path = pages.at(2);
	}
	else if (pages.at(1) == "501")
	{
		if (DEBUG)
			std::cout << DBG << "[HttpRequestConfig::SetErrorPages] setting error page 501 to:" << pages.at(2) << std::endl;
		this->_errpages[E501].path = pages.at(2);
	}
	else if (pages.at(1) == "505")
	{
		if (DEBUG)
			std::cout << DBG << "[HttpRequestConfig::SetErrorPages] setting error page 505 to:" << pages.at(2) << std::endl;
		this->_errpages[E505].path = pages.at(2);
	}
	else
		return (ERRPARSE_ERRPAGE);
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetRoot(const std::vector<std::string> &root)
{
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetRoot] setting root" << std::endl;
	if (root.size() != 2)
		return (ERRPARSE_NBARGS);
	this->_root = root.at(1);
	if (this->_root.at(this->_root.size() - 1) != '/')
		this->_root += '/';
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetRoot] root set to: " << this->GetRoot() << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetMaxPostSize(const std::vector<std::string> &max_size_post)
{
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetMaxPostSize] setting max post size" << std::endl;
	if (std::atof(max_size_post.at(1).c_str()) < 0 || std::atof(max_size_post.at(1).c_str()) == HUGE_VAL)
		return (ERRPARSE_POST);
	this->_max_size_post = std::atof(max_size_post.at(1).c_str());
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetMaxPostSize] max post size set to: " << this->GetMaxPostSize() << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetSessionPath(const std::vector<std::string> &sessionpath)
{
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetSessionPath] setting session path" << std::endl;
	this->_sessionpath = sessionpath.at(1);
	if (this->_sessionpath.at(this->_sessionpath.size() - 1) != '/')
		this->_sessionpath += '/';
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetSessionPath] session path set to: " << this->GetSessionPath() << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetCookies(const std::vector<std::string> &cookies)
{
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetCookies] setting cookies" << std::endl;
	std::string tmp = cookies.at(1);
	LOWERCASE(tmp);
	if (tmp == "on")
		this->_cookies = true;
	else if (tmp == "off")
		this->_cookies = false;
	else
		return (ERRPARSE_COOKIES);
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetCookies] cookies set to: " << this->GetCookies() << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetUploads(const std::vector<std::string> &uploads)
{
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetUploads] setting uploads" << std::endl;
	std::string tmp = uploads.at(1);
	LOWERCASE(tmp);
	if (tmp == "on")
		this->_uploads = true;
	else if (tmp == "off")
		this->_uploads = false;
	else
		return (ERRPARSE_UPLOADS);
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetUploads] uploads set to: " << this->GetUploads() << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetDirList(const std::vector<std::string> &dirlist)
{
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetDirList] setting dir list" << std::endl;
	std::string tmp = dirlist.at(1);
	LOWERCASE(tmp);
	if (tmp == "on")
		this->_dirlist = true;
	else if (tmp == "off")
		this->_dirlist = false;
	else
		return (ERRPARSE_DIRLIST);
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetDirList] dir list set to: " << this->GetDirList() << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetCgi(const std::vector<std::string> &cgi)
{
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetCgi] setting cgi" << std::endl;
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
		std::cout << DBG << "[HttpRequestConfig::SetCgi] cgi: " << cgi.at(1) << " -> " << this->_cgi[cgi.at(1)] << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetMethods(const std::vector<std::string> &methods)
{
	int	tmp = 0;
	std::string tmpstr;
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetMethods] setting methods" << std::endl;
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
		std::cout << DBG << "[HttpRequestConfig::SetMethods] methods set to: " << this->GetMethods() << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetUploadDir(const std::vector<std::string> &uploaddir)
{
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetUploadDir] setting upload dir" << std::endl;
	this->_uploaddir = uploaddir.at(1);
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetUploadDir] upload dir set to: " << this->GetUploadDir() << std::endl;
	return (ERRPARSE_OK);
}
t_errcode	HttpRequestConfig::SetHttpResponseCode(const std::vector<std::string> &argv)
{
	(void)argv;
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetHttpResponseCode] setting http response code" << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetRedirect(const std::vector<std::string> &argv)
{
	(void)argv;
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetRedirect] setting redirect" << std::endl;
	return (ERRPARSE_OK);
}
