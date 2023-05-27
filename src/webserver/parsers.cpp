/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:28:25 by ldournoi          #+#    #+#             */
/*   Updated: 2023/05/24 16:52:41 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_utils.hpp"
#include "webserver.hpp"
#include "http_config.hpp"
#include "http_request_config.hpp"
#include "logger.hpp"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>

t_errcode WebServer::_parseSrvDirective(const std::string& line)
{
	HttpServerConfig			*srv;
	std::vector<std::string>	argv;
	std::string					arg;
	std::string					tmp;
	int							argc;
	t_errcode					err;

	logz.log(L_DEBUG, "parsing server directive: " + line);
	srv = this->_configs.at(this->_nserv - 1);
	argv = this->_splitDirective(line);
	arg = argv.at(0);
	argc = argv.size();
	logz.log(L_DEBUG, "arg: " + arg + " argc: " + logz.itoa(argc));
	switch (argc){
		case 0:
			return (ERRPARSE_OK);
		case 1:
			if (argv.at(0) == "}")
			{
				logz.log(L_DEBUG, "end of server block");
				return (ERRPARSE_OK);
			}
			return (ERRPARSE_SINGLEARG);
	}
	if (arg.at(0) == '/' || arg.at(0) == '#')
	{
		logz.log(L_DEBUG, "directive: " + arg + "is a comment");
		return (ERRPARSE_OK);
	}
	if (argv.back() == "}"){
		argv.pop_back();
		argc--;
	}
	if (argv.back().at(argv.back().size() - 1) == '}'){
		argv.back().erase(argv.back().end() - 1);
	}
	tmp = "line: " O + this->_line;
	try{
		HttpServerConfig::t_parseMap callback;
		callback = srv->GetParseMap().at(arg);
		err = (srv->*callback)(argv);
		if (err != ERRPARSE_OK)
		{
			logz.logerr(L_ERROR | L_BYPASS, tmp + " " + R + this->GetErrorStrs().at(err) + RST);
			return (err);
		}
	}catch (std::out_of_range& e){
		logz.logerr(L_ERROR | L_BYPASS, tmp + " " + RST " unknown directive: " + arg);
		return (ERRPARSE_UNKNOWN);
	}
	return (ERRPARSE_OK);
}

t_errcode WebServer::_parseLocDirective(const std::string& line)
{
	HttpRequestConfig*			loc = this->_configs.at(this->_nserv - 1)->GetRequestConfigs().back();
	std::vector<std::string>	argv;
	std::string					arg;
	std::string					tmp;
	int							argc;
	t_errcode					err;

	argv = this->_splitDirective(line);
	arg = argv.at(0);
	argc = argv.size();
	switch (argc){
		case 0:
			return (ERRPARSE_OK);
		case 1:
			if (argv.at(0) == "}")
			{
				logz.log(L_DEBUG, "end of location block");
				return (ERRPARSE_OK);
			}
			return (ERRPARSE_SINGLEARG);
	}
	if (arg.at(0) == '/' || arg.at(0) == '#')
	{
		logz.log(L_DEBUG, "directive: " + arg + " is a comment");
		return (ERRPARSE_OK);
	}
	if (argv.back() == "}"){
		argv.pop_back();
		argc--;
	}
	if (argv.back().at(argv.back().size() - 1) == '}'){
		argv.back().erase(argv.back().end() - 1);
	}
	tmp = "line: " O + this->_line;
	try{
		HttpRequestConfig::t_parseMap callback;
		callback = loc->GetParseMap().at(arg);
		err = (loc->*callback)(argv);
		if (err != ERRPARSE_OK)
		{
			logz.logerr(L_ERROR | L_BYPASS, tmp + " " + R + this->GetErrorStrs().at(err) + RST);
			return (err);
		}
	}catch (std::out_of_range& e){
		logz.logerr(L_ERROR | L_BYPASS, tmp + " " + RST " unknown directive: " + arg);
		return (ERRPARSE_UNKNOWN);
	}
	return (ERRPARSE_OK);
}
