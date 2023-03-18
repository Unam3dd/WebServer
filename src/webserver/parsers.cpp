/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:28:25 by ldournoi          #+#    #+#             */
/*   Updated: 2023/03/18 12:04:41 by ldournoi         ###   ########.fr       */
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
					std::cout << DBG << "End of server block" << std::endl;
				return (ERRPARSE_ENDBLK);
			}
			return (ERRPARSE_SINGLEARG);
	}
	if (arg == "server_name" || arg == "server_names")
	{
		if (DEBUG)
			std::cout << DBG << "[_parseSrvDirective] server_name: '" << argv.at(1) << "'" << std::endl;
		srv.SetServerNames(argv);
	}
	return (ERRPARSE_OK);
}

t_errcode WebServer::_parseLocDirective(const std::string& line)
{
	(void)line;
	return (ERRPARSE_OK);
}
