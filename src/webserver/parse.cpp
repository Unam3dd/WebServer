/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:35:50 by stales            #+#    #+#             */
/*   Updated: 2023/03/17 20:07:03 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserver.hpp"
#include "http_colors.hpp"
#include <iostream>

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
		if (DEBUG)
		{
			std::cout << DBG << "[WebServer::Parse]\t";
			this->_srvBlk ? std::cout << "srvblk::": std::cout << "!srvblk::";
			this->_locBlk ? std::cout << "locblk::": std::cout << "!locblk::";
			std::cout << line << std::endl;
		}
		if (line.empty() || line.size() == 0)
		{
			buffer = buffer.substr(buffer.find("\n") + 1);
			continue;
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
			this->_initNewLocBlk();
		}
		else if (this->_srvBlk && this->_locBlk && this->_isEndBlk(line))
		{
			t_errcode err = this->_parseLocBlk(line);
			if (err != ERRPARSE_OK)
				return (err);
			this->_locBlk = false;
		}
		else if (this->_srvBlk && !this->_locBlk && this->_isEndBlk(line))
		{
			t_errcode err = this->_parseSrvBlk(line);
			if (err != ERRPARSE_OK)
				return (err);
			this->_srvBlk = false;
		}
		else if (!this->_srvBlk && !this->_locBlk && this->_isEndBlk(line))
			return (ERRPARSE_ENDBLK);
		else if (this->_srvBlk && !this->_locBlk && (!line.empty() || line.find_first_not_of(" \t") != std::string::npos))
		{
			t_errcode err = this->_parseSrvBlk(line);
			if (err != ERRPARSE_OK)
				return (err);
		}
		else if (this->_srvBlk && this->_locBlk && (!line.empty() || line.find_first_not_of(" \t") != std::string::npos))
		{
			t_errcode err = this->_parseLocBlk(line);
			if (err != ERRPARSE_OK)
				return (err);
		}
		buffer = buffer.substr(buffer.find("\n") + 1);
	}
	return (0);
}
