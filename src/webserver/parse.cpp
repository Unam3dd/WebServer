/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:35:50 by stales            #+#    #+#             */
/*   Updated: 2023/05/27 00:09:32 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config.hpp"
#include "http_utils.hpp"
#include "webserver.hpp"
#include <iostream>
#include <algorithm>

t_errcode WebServer::Parse(void)
{
	std::string line;
	std::string buffer;
	std::string tmp;
	std::string red_line;

	if (!this->size())
		return (ERRPARSE_UNKNOWN);

	buffer = static_cast<std::string>(this->_cfgfile.getData());
	_line = 0;
	while (!buffer.empty())
	{
		line = buffer.substr(0, buffer.find("\n"));
		_line++;
		red_line = "line ";
		red_line += R + logz.itoa(_line) + RST;
		line.erase(0, line.find_first_not_of(" \t"));
		if (line.empty() || line.size() == 0)
		{
			buffer = buffer.substr(buffer.find("\n") + 1);
			continue;
		}
		tmp = this->_srvBlk ? ANSI_FMT(G, "srvblk::") : ANSI_FMT(R, "!srvblk::");
		tmp += this->_locBlk ? ANSI_FMT(G, "locblk") : ANSI_FMT(R, "!locblk");
		tmp += " " + line;
		logz.log(1, tmp);
		if (this->_isSrvBlk(line))
		{
			if (this->_srvBlk == true)
			{
				logz.log(2, red_line + " new server block before end of previous one");
				return (ERRPARSE_NEWSRVBLK);
			}
			this->_srvBlk = true;
			this->_initNewSrvBlk();
		}
		else if (this->_srvBlk && this->_isLocBlk(line))
		{
			if (this->_locBlk == true)
			{
				logz.log(2, red_line + " new location block before end of previous one");
				return (ERRPARSE_NEWLOCBLK);
			}
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
		{
			logz.log(2, red_line + " end of block without any block opened");
			return (ERRPARSE_ENDBLK);
		}
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
	if (this->_srvBlk == true)
	{
		logz.log(2, red_line + " unclosed server block");
		return (ERRPARSE_NEWSRVBLK);
	}
	if (this->_locBlk == true)
	{
		logz.log(2, red_line + " unclosed location block");
		return (ERRPARSE_NEWLOCBLK);
	}
	int i = 0;
	FOREACH_VECTOR(HttpServerConfig *, this->_configs, it)
	{
		tmp = R "config #" RST + logz.itoa(i + 1);
		if ((*it)->GetServerNames().empty())
		{
			logz.log(2, tmp + " server name is empty");
			return (ERRPARSE_NOSRVNAME);
		}
		if ((*it)->GetServerPorts().empty())
		{
			logz.log(2, tmp + " server port is empty");
			return (ERRPARSE_NOPORT);
		}
	}
	return (ERRPARSE_OK);
}
