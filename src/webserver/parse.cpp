/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:35:50 by stales            #+#    #+#             */
/*   Updated: 2023/03/18 17:23:56 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserver.hpp"
#include "http_colors.hpp"
#include <iostream>
#include <algorithm>

int	WebServer::Parse(const std::string& path)
{
	if (path.empty()) return (1);
	std::cout << this->getData() << std::endl;
	return (0);
}

int	WebServer::Parse(void)
{
	std::string line;
	std::string buffer;

	buffer = static_cast<std::string>(this->getData());
	while (!buffer.empty())
	{
		line = buffer.substr(0, buffer.find("\n"));
		line.erase(0, line.find_last_of("\t") + 1);
		if (line.empty() || line.size() == 0)
		{
			buffer = buffer.substr(buffer.find("\n") + 1);
			continue;
		}
		if (DEBUG)
		{
			std::cout << DBG << "[WebServer::Parse]";
			this->_srvBlk ? std::cout << GREEN << "srvblk::" << RESET: std::cout << RED << "!srvblk::" << RESET;
			this->_locBlk ? std::cout << GREEN << "locblk\t" << RESET: std::cout << RED << "!locblk\t" << RESET;
			std::cout << BGBLACK << line << RESET << std::endl;
		}
		if (this->_isSrvBlk(line))
		{
			if (this->_srvBlk == true)
				return (ERRPARSE_NEWSRVBLK);
			this->_srvBlk = true;
			this->_initNewSrvBlk();
		}
		else if (this->_srvBlk && this->_isLocBlk(line))  
		{
			if (this->_locBlk == true)
				return (ERRPARSE_NEWLOCBLK);
			this->_locBlk = true;
			t_errcode err = this->_initNewLocBlk(line);
			if (err != ERRPARSE_OK)
				return (err);
		}
		else if (this->_srvBlk && this->_locBlk && this->_isEndBlk(line))
		{
			t_errcode err = this->_parseLocDirective(line);
			if (err != ERRPARSE_OK)
				return (err);
			this->_locBlk = false;
		}
		else if (this->_srvBlk && !this->_locBlk && this->_isEndBlk(line))
		{
			t_errcode err = this->_parseSrvDirective(line);
			if (err != ERRPARSE_OK)
				return (err);
			this->_srvBlk = false;
		}
		else if (!this->_srvBlk && !this->_locBlk && this->_isEndBlk(line))
			return (ERRPARSE_ENDBLK);
		else if (this->_srvBlk && !this->_locBlk && (!line.empty() || line.find_first_not_of(" \t") != std::string::npos))
		{
			t_errcode err = this->_parseSrvDirective(line);
			if (err != ERRPARSE_OK)
				return (err);
		}
		else if (this->_srvBlk && this->_locBlk && (!line.empty() || line.find_first_not_of(" \t") != std::string::npos))
		{
			t_errcode err = this->_parseLocDirective(line);
			if (err != ERRPARSE_OK)
				return (err);
		}
		buffer = buffer.substr(buffer.find("\n") + 1);
	}
	return (0);
}
