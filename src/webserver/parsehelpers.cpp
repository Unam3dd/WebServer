/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsehelpers.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:16:47 by ldournoi          #+#    #+#             */
/*   Updated: 2023/03/17 20:20:44 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config.hpp"
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
	if (tmp.compare("server{" ) == 0 || tmp.compare("server") == 0)
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
	std::stringstream ss(tmp);
	std::string token;

	while (std::getline(ss, token, ' '))
	{
		SANITIZE_SPACES(token);
		if (!token.empty())
			ret.push_back(token);
	}
	return (ret);
}

void	WebServer::_initNewSrvBlk()
{
	this->_configs.push_back(HttpServerConfig());
	this->_nserv += 1;
}

void	WebServer::_initNewLocBlk()
{
}
