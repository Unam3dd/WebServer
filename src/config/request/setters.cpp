/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:59:57 by ldournoi          #+#    #+#             */
/*   Updated: 2023/03/20 00:01:02 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_request_config.hpp"
#include "http_colors.hpp"
#include "http_utils.hpp"
#include "utils.hpp"
#include "webserver.hpp"
#include <cstdlib>
#include <iostream>

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
	(void)pages;
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetErrorPages] setting error pages" << std::endl;
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

t_errcode	HttpRequestConfig::SetRoot(const std::vector<std::string> &root)
{
	(void)root;
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetRoot] setting root" << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetMaxPostSize(const std::vector<std::string> &max_size_post)
{
	(void)max_size_post;
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetMaxPostSize] setting max post size" << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetSessionPath(const std::vector<std::string> &sessionpath)
{
	(void)sessionpath;
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetSessionPath] setting session path" << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetServerTimeout(const std::vector<std::string> &sessiontimeout)
{
	(void)sessiontimeout;
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetServerTimeout] setting session timeout" << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetCookies(const std::vector<std::string> &cookies)
{
	(void)cookies;
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetCookies] setting cookies" << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetUploads(const std::vector<std::string> &uploads)
{
	(void)uploads;
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetUploads] setting uploads" << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetDirList(const std::vector<std::string> &dirlist)
{
	(void)dirlist;
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetDirList] setting dir list" << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetCgi(const std::vector<std::string> &cgi)
{
	(void)cgi;
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetCgi] setting cgi" << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetMethods(const std::vector<std::string> &methods)
{
	(void)methods;
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetMethods] setting methods" << std::endl;
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetUploadDir(const std::vector<std::string> &uploaddir)
{
	(void)uploaddir;
	if (DEBUG)
		std::cout << DBG << "[HttpRequestConfig::SetUploadDir] setting upload dir" << std::endl;
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
