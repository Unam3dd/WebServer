/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:28:25 by ldournoi          #+#    #+#             */
/*   Updated: 2023/03/17 19:23:30 by ldournoi         ###   ########.fr       */
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
	HttpServerConfig	srv = this->_configs.at(this->_nserv - 1);
	std::vector<std::string>	argv;
	int							argc;	

	argv = this->_splitDirective(line);
	argc = argv.size();
	if (DEBUG)
	{
		std::cout << DBG << "line: " << line << "\targc: " << argc << std::endl;
	}
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
					std::cout << DBG << "Listen directive " << argv.at(1) << std::endl;
				srv.SetServerPorts(argv);
			}
			else if (argv.at(0) == "server_name")
			{
				if (DEBUG)
					std::cout << DBG << "Server name directive " << argv.at(1) << std::endl;
				srv.SetServerNames(argv);
			}
			else if (argv.at(0) == "docroot")
			{
				if (DEBUG)
					std::cout << DBG << "Docroot directive " << argv.at(1) << std::endl;
				srv.SetRoot(argv.at(1));
			}
			else if (argv.at(0) == "errpage")
			{
				if (DEBUG)
					std::cout << DBG << "Error page directive " << argv.at(1) << std::endl;
				srv.SetErrorPages(argv);
			}
			else if (argv.at(0) == "index")
			{
				if (DEBUG)
					std::cout << DBG << "Index directive " << argv.at(1) << std::endl;
				srv.SetIndexes(argv);
			}
			else if (argv.at(0) == "client_max_body_size")
			{
				if (DEBUG)
					std::cout << DBG << "Client max body size directive " << argv.at(1) << std::endl;
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
