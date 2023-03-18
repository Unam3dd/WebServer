/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:28:25 by ldournoi          #+#    #+#             */
/*   Updated: 2023/03/18 16:16:30 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_utils.hpp"
#include "webserver.hpp"
#include "http_config.hpp"
#include "http_request_config.hpp"
#include "http_colors.hpp"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>

t_errcode WebServer::_parseSrvDirective(const std::string& line)
{
	HttpServerConfig			srv = this->_configs.at(this->_nserv - 1);
	std::vector<std::string>	argv;
	std::string					arg;
	int							argc;	

	argv = this->_splitDirective(line);
	arg = argv.at(0);
	argc = argv.size();
	switch (argc){
		case 0:
			return (ERRPARSE_OK);
		case 1:
			if (argv.at(0) == "}")
			{
				if (DEBUG)
					std::cout << DBG << "[_parseSrvDirective] end of server block" << std::endl;
				return (ERRPARSE_ENDBLK);
			}
			return (ERRPARSE_SINGLEARG);
	}
	try{
		HttpServerConfig::t_parseMap callback;
		callback = srv.GetParseMap().at(arg);
		t_errcode err = (srv.*callback)(argv);
		if (err != ERRPARSE_OK)
			return (err);
	}catch (std::out_of_range& e){
		if (DEBUG)
			std::cerr << DBG << "[_parseSrvDirective]" << RED << "[ERROR] unknown directive: " << arg << RESET << std::endl;
		return (ERRPARSE_UNKNOWN);
	}
	return (ERRPARSE_OK);
}

t_errcode WebServer::_parseLocDirective(const std::string& line)
{
	(void)line;
	return (ERRPARSE_OK);
}
