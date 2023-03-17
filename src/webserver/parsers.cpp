/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:28:25 by ldournoi          #+#    #+#             */
/*   Updated: 2023/03/17 20:25:00 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserver.hpp"
#include "http_config.hpp"
#include "http_request_config.hpp"
#include "http_colors.hpp"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>

t_errcode WebServer::_parseSrvBlk(const std::string& line)
{
	HttpServerConfig			srv = this->_configs.at(this->_nserv - 1);
	std::vector<std::string>	argv;
	int							argc;	

	argv = this->_splitDirective(line);
	argc = argv.size();
	switch (argc){
		case 0:
			return (ERRPARSE_OK);
		case 1:
			if (argv.at(0) == "}")
			{
				if (DEBUG)
					std::cout << DBG << "End of server block" << std::endl;
				return (ERRPARSE_ENDBLK);
			}
			return (ERRPARSE_SINGLEARG);
		case 2:
			if (argv.at(0) == "listen")
			{
				if (DEBUG)
					std::cout << DBG << "[WebServer::_parseSrvBlk]listen: '" << argv.at(1) << "'\n";
				srv.SetServerPorts(argv);
			}
			else if (argv.at(0) == "server_name" || argv.at(0) == "server_names")
			{
				if (DEBUG)
					std::cout << DBG << "[WebServer::_parseSrvBlk]server_name: '" << argv.at(1) << "'\n";
				srv.SetServerNames(argv);
			}
			else if (argv.at(0) == "docroot")
			{
				if (DEBUG)
					std::cout << DBG << "[WebServer::_parseSrvBlk]docroot: '" << argv.at(1) << "'\n";
				srv.SetRoot(argv.at(1));
			}
			else if (argv.at(0) == "errpage")
			{
				if (DEBUG)
					std::cout << DBG << "[WebServer::_parseSrvBlk]errpage: '" << argv.at(1) << "'\n";
				srv.SetErrorPages(argv);
			}
			else if (argv.at(0) == "index")
			{
				if (DEBUG)
					std::cout << DBG << "[WebServer::_parseSrvBlk]index: '" << argv.at(1) << "'\n";
				srv.SetIndexes(argv);
			}
			else if (argv.at(0) == "client_max_body_size")
			{
				if (DEBUG)
					std::cout << DBG << "[WebServer::_parseSrvBlk]client max body size: '" << argv.at(1) << "'\n";
				srv.SetMaxPostSize(argv.at(1));
			}
			else
				return (ERRPARSE_UNKNOWN);
			break;

	}
	return (ERRPARSE_OK);
}

t_errcode WebServer::_parseLocBlk(const std::string& line)
{
	(void)line;
	return (ERRPARSE_OK);
}
