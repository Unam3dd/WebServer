/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:59:57 by ldournoi          #+#    #+#             */
/*   Updated: 2023/05/27 10:24:11 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_request_config.hpp"
#include "logger.hpp"
#include "http_utils.hpp"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>

t_errcode	HttpRequestConfig::SetIndexes(const std::vector<std::string> &indexs)
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

t_errcode	HttpRequestConfig::SetErrorPages(const std::vector<std::string> &pages)
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

t_errcode	HttpRequestConfig::SetRoot(const std::vector<std::string> &root)
{

	logz.log(L_DEBUG, "setting root");
	if (root.size() != 2) return (ERRPARSE_NBARGS);
	this->_root = root.at(1);
	if (this->_root.at(this->_root.size() - 1) != '/')
		this->_root += '/';
	logz.log(L_DEBUG, "root set to: " + this->GetRoot());
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetMaxPostSize(const std::vector<std::string> &max_size_post)
{
	std::string tmp = max_size_post.at(1);
	logz.log(L_DEBUG, "settings max post size");
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
	logz.log(L_DEBUG, "max post size set to (in bytes): " + logz.itoa(this->GetMaxPostSize()));
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetCookies(const std::vector<std::string> &cookies)
{
	logz.log(L_DEBUG, "setting cookies");
	if (cookies.size() != 2)
		return (ERRPARSE_COOKIES);
	std::string tmp = cookies.at(1);
	LOWERCASE(tmp);
	if (tmp == "on")
		this->_cookies = true;
	else if (tmp == "off")
		this->_cookies = false;
	else
		return (ERRPARSE_COOKIES);
	logz.log(L_DEBUG, "cookies set to: " + this->GetCookies());
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetUploads(const std::vector<std::string> &uploads)
{
	logz.log(L_DEBUG, "setting uploads");
	if (uploads.size() != 2)
		return (ERRPARSE_UPLOADS);
	std::string tmp = uploads.at(1);
	LOWERCASE(tmp);
	if (tmp == "on")
		this->_uploads = true;
	else if (tmp == "off")
		this->_uploads = false;
	else
		return (ERRPARSE_UPLOADS);

	logz.log(L_DEBUG, "uploads set to: " + this->GetUploads());
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetDirList(const std::vector<std::string> &dirlist)
{
	logz.log(L_DEBUG, "setting dir list");
	if (dirlist.size() != 2)
		return (ERRPARSE_DIRLIST);
	std::string tmp = dirlist.at(1);
	LOWERCASE(tmp);
	if (tmp == "on")
		this->_dirlist = true;
	else if (tmp == "off")
		this->_dirlist = false;
	else
		return (ERRPARSE_DIRLIST);
	logz.log(L_DEBUG, "dir list set to: " + this->GetDirList());
	return (ERRPARSE_OK);
}

t_errcode	HttpRequestConfig::SetCgi(const std::vector<std::string> &cgi)
{
	logz.log(L_DEBUG, "setting cgi");
	if (cgi.size() != 3)
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

t_errcode	HttpRequestConfig::SetMethods(const std::vector<std::string> &methods)
{
	int	tmp = 0;
	std::string tmpstr;
	logz.log(L_DEBUG, "settings methods");
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

t_errcode	HttpRequestConfig::SetHttpResponseCode(const std::vector<std::string> &argv)
{
	logz.log(L_DEBUG, "setting http reponse code");
	std::string code = argv.at(1);
	if (code.size() != 3)
		return (ERRPARSE_HTTPCODE);
	for (size_t i = 0; i < code.size(); i++)
	{
		if (!isdigit(code.at(i)))
			return (ERRPARSE_HTTPCODE);
	}
	this->_response_code = atoi(code.c_str());
	if (this->_response_code != 100 && this->_response_code != 101 && this->_response_code != 200 &&
		this->_response_code != 201 && this->_response_code != 202 && this->_response_code != 203 &&
		this->_response_code != 204 && this->_response_code != 205 && this->_response_code != 206 &&
		this->_response_code != 300 && this->_response_code != 301 && this->_response_code != 302 &&
		this->_response_code != 303 && this->_response_code != 304 && this->_response_code != 305 &&
		this->_response_code != 307 && this->_response_code != 400 && this->_response_code != 401 &&
		this->_response_code != 402 && this->_response_code != 403 && this->_response_code != 404 &&
		this->_response_code != 405 && this->_response_code != 406 && this->_response_code != 407 &&
		this->_response_code != 408 && this->_response_code != 409 && this->_response_code != 410 &&
		this->_response_code != 411 && this->_response_code != 412 && this->_response_code != 413 &&
		this->_response_code != 414 && this->_response_code != 415 && this->_response_code != 416 &&
		this->_response_code != 417 && this->_response_code != 500 && this->_response_code != 501 &&
		this->_response_code != 502 && this->_response_code != 503 && this->_response_code != 504 &&
		this->_response_code != 505)
		return (ERRPARSE_HTTPCODE);
	return (ERRPARSE_OK);
}
