/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:02:17 by stales            #+#    #+#             */
/*   Updated: 2023/03/10 16:45:42 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config_parser.hpp"
#include "utils.hpp"
#include <cstdlib>
#include <iostream>
#include <cstring>

int HttpConfigParser::parse_token(const std::string& str)
{
	if (str.empty()) return (1);
	std::string nstr = "";
	size_t	spaces = 0;
	config_tokens_t type = CONFIG_TOKEN_INVALID;

	spaces = std::strspn(str.c_str(), " \t\n");
	if (spaces == str.size()) return (1);

	spaces = std::strcspn(str.c_str(), " \t");
	if (spaces == str.size() || !spaces)
		return (1);

	nstr = str.substr(0, spaces);
	if (nstr.empty()) return (1);

	type = GetTypeToken(nstr);
	if (type == CONFIG_TOKEN_INVALID) return (false);

	std::cout << "TOKEN READED " << GetStringToken(type) << std::endl;

	return (0);
}

int	HttpConfigParser::read_token(const std::string& str, config_tokens_t token)
{
	if (str.empty()) return (1);

	if (token == CONFIG_TOKEN_ADDR)
		this->_ip = str;
	else if (token == CONFIG_TOKEN_PORT && str.at(0) != '-' && !check_overflow_short(str))
		this->_port = (port_t)std::atoi(str.c_str());
	return (0);
}

parse_config_status_t	HttpConfigParser::Parse(const HttpConfig& c)
{
	if (!c.getData() || !c.length())
		return (CONFIG_LOADED_FAILED);

	std::string	str(c.getData());

	size_t	ln = 0;
	size_t	start = 0;

	ln = str.find("\n");

	while (ln != std::string::npos)
	{
		if (parse_token(str.substr(start, ln))) return (CONFIG_LOADED_FAILED);
		start += ln+1;
		ln = str.find("\n", start);
	}
	return (CONFIG_LOADED_SUCCESS);
}
