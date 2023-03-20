/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:28:25 by ldournoi          #+#    #+#             */
/*   Updated: 2023/03/20 01:06:19 by ldournoi         ###   ########.fr       */
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
	HttpServerConfig			*srv;
	std::vector<std::string>	argv;
	std::string					arg;
	int							argc;	

	if (DEBUG)
		std::cout << DBG << "[WebServer::_parseSrvDirective] parsing server directive: " << line << std::endl;
	srv = this->_configs.at(this->_nserv - 1);
	argv = this->_splitDirective(line);
	arg = argv.at(0);
	argc = argv.size();
	if (DEBUG)
		std::cout << DBG << "[WebServer::_parseSrvDirective] arg: " << arg << "\targc: " << argc << std::endl;
	switch (argc){
		case 0:
			return (ERRPARSE_OK);
		case 1:
			if (argv.at(0) == "}")
			{
				if (DEBUG)
					std::cout << DBG << "[_parseSrvDirective] end of server block" << std::endl;
				return (ERRPARSE_OK);
			}
			return (ERRPARSE_SINGLEARG);
	}
	if (arg == "/" || arg == "//" || arg == "#" || arg == "/*")
		return (ERRPARSE_OK);
	try{
		HttpServerConfig::t_parseMap callback;
		callback = srv->GetParseMap().at(arg);
		t_errcode err = (srv->*callback)(argv);
		if (err != ERRPARSE_OK)
			return (err);
	}catch (std::out_of_range& e){
		if (DEBUG)
			std::cerr << FAIL << "[_parseSrvDirective]" << RED << " unknown directive: " << arg << RESET << std::endl;
		return (ERRPARSE_UNKNOWN);
	}
	return (ERRPARSE_OK);
}

t_errcode WebServer::_parseLocDirective(const std::string& line)
{
	HttpRequestConfig			loc = this->_configs.at(this->_nserv - 1)->GetRequestConfigs().back();
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
					std::cout << DBG << "[_parseLocDirective] end of location block" << std::endl;
				return (ERRPARSE_OK);
			}
			return (ERRPARSE_SINGLEARG);
	}
	if (arg == "/" || arg == "//" || arg == "#" || arg == "/*")
		return (ERRPARSE_OK);
	try{
		HttpRequestConfig::t_parseMap callback;
		callback = loc.GetParseMap().at(arg);
		t_errcode err = (loc.*callback)(argv);
		if (err != ERRPARSE_OK)
			return (err);
	}catch (std::out_of_range& e){
		if (DEBUG)
			std::cerr << FAIL << "[_parseLocDirective]" << RED << " unknown directive: " << arg << RESET << std::endl;
		return (ERRPARSE_UNKNOWN);
	}
	return (ERRPARSE_OK);
}
