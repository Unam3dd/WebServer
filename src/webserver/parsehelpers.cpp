/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsehelpers.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:16:47 by ldournoi          #+#    #+#             */
/*   Updated: 2023/05/24 16:13:07 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config.hpp"
#include "logger.hpp"
#include "http_utils.hpp"
#include "webserver.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>

bool	WebServer::_isSrvBlk(const std::string& line)
{
	std::string tmp = line;
	//remove all spaces
	tmp.erase(std::remove(tmp.begin(), tmp.end(), ' '), tmp.end());
	//remove all tabs
	tmp.erase(std::remove(tmp.begin(), tmp.end(), '\t'), tmp.end());
	if (tmp.compare("server{" ) == 0)
		return (true);
	return (false);
}

bool	WebServer::_isLocBlk(const std::string& line)
{
	std::string tmp = line;
	//remove all spaces
	tmp.erase(std::remove(tmp.begin(), tmp.end(), ' '), tmp.end());
	//remove all tabs
	tmp.erase(std::remove(tmp.begin(), tmp.end(), '\t'), tmp.end());
	if (  !tmp.empty() && tmp.length() >= 8 && tmp.substr(0, 8).compare("location") == 0 \
		&& tmp.at(tmp.size() - 1) == '{' && std::count(tmp.begin(), tmp.end(), '{') == 1)
		return (true);
	return (false);
}

bool	WebServer::_isEndBlk(const std::string& line)
{
	std::string tmp = line;
	//remove all spaces
	tmp.erase(std::remove(tmp.begin(), tmp.end(), ' '), tmp.end());
	//remove all tabs
	tmp.erase(std::remove(tmp.begin(), tmp.end(), '\t'), tmp.end());
	if (!tmp.empty() && tmp.at(tmp.length() - 1) == '}' && std::count(tmp.begin(), tmp.end(), '}') == 1)
		return (true);
	return (false);
}

std::vector<std::string> WebServer::_splitDirective(const std::string& directive)
{
	std::vector<std::string> ret;
	std::string tmp = directive;
	std::string token;

	while (!tmp.empty())
	{
		token = tmp.substr(0, tmp.find_first_of(" \t"));
		if (token.empty())
		{
			tmp = tmp.substr(tmp.find_first_of(" \t") + 1);
			continue;
		}
		ret.push_back(token);
		if (tmp.find_first_of(" \t") == std::string::npos)
			break;
		tmp = tmp.substr(tmp.find_first_of(" \t") + 1);
	}
	return (ret);
}

void	WebServer::_initNewSrvBlk()
{
	std::string	tmp;

	tmp = "entering function. previous _nserv: " + logz.itoa(this->_nserv);
	tmp += " _configs.size(): " + logz.itoa(_configs.size());
	logz.log(L_DEBUG, tmp);
	this->_configs.push_back(new HttpServerConfig());
	this->_nserv += 1;
	tmp = "successful. new _nserv: " + logz.itoa(this->_nserv);
	tmp += " _configs.size(): " + logz.itoa(_configs.size());
	logz.log(L_DEBUG, tmp);
}

t_errcode	WebServer::_initNewLocBlk(const std::string& line)
{
	HttpServerConfig* srv = this->_configs.at(this->_nserv - 1);
	std::string scope = line.substr(9, line.find_first_of("{") - 9);

	logz.log(L_DEBUG, "scope: " + scope);
	if (scope.empty())
		return (ERRPARSE_NEWLOCBLK);
	srv->initNewLocBlk(scope);
	return (ERRPARSE_OK);
}
