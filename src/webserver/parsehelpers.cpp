/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsehelpers.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:16:47 by ldournoi          #+#    #+#             */
/*   Updated: 2023/03/17 15:59:28 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserver.hpp"
#include <iostream>
#include <algorithm>

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
