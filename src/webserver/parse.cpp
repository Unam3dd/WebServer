/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:35:50 by stales            #+#    #+#             */
/*   Updated: 2023/03/17 16:01:36 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserver.hpp"
#include <iostream>

int	WebServer::Parse(const std::string& path)
{
	if (path.empty()) return (1);
	std::cout << this->getData() << std::endl;
	return (0);
}

int	WebServer::Parse(void)
{
	bool srvBlk = false;
	bool locBlk = false;
	std::string line;
	std::string buffer;

	buffer = static_cast<std::string>(this->getData());
	while (!buffer.empty())
	{
		line = buffer.substr(0, buffer.find("\n"));
		if (DEBUG)
		{
			srvBlk ? std::cout << "srvblk::": std::cout << "!srvblk::";
			locBlk ? std::cout << "locblk::": std::cout << "!locblk::";
			std::cout << line << std::endl;
		}
		if (line.empty() || line.size() == 0)
		{
			buffer = buffer.substr(buffer.find("\n") + 1);
			continue;
		}
		if (this->_isSrvBlk(line))
		{
			if (srvBlk == true)
				return (ERRPARSE_NEWSRVBLK);
			srvBlk = true;
		}
		else if (srvBlk && this->_isLocBlk(line))  
		{
			if (locBlk == true)
				return (ERRPARSE_NEWLOCBLK);
			locBlk = true;
		}
		else if (srvBlk && locBlk && this->_isEndBlk(line))
		{
			t_errcode err = this->_parseLocBlk(line);
			if (err != ERRPARSE_OK)
				return (err);
			locBlk = false;
		}
		else if (srvBlk && !locBlk && this->_isEndBlk(line))
		{
			t_errcode err = this->_parseSrvBlk(line);
			if (err != ERRPARSE_OK)
				return (err);
			srvBlk = false;
		}
		else if (!srvBlk && !locBlk && this->_isEndBlk(line))
			return (ERRPARSE_ENDBLK);
		else if (srvBlk && !locBlk && (!line.empty() || line.find_first_not_of(" \t") != std::string::npos))
		{
			t_errcode err = this->_parseSrvBlk(line);
			if (err != ERRPARSE_OK)
				return (err);
		}
		else if (srvBlk && locBlk && (!line.empty() || line.find_first_not_of(" \t") != std::string::npos))
		{
			t_errcode err = this->_parseLocBlk(line);
			if (err != ERRPARSE_OK)
				return (err);
		}
		buffer = buffer.substr(buffer.find("\n") + 1);
	}
	return (0);
}
