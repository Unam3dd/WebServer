/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:02:17 by stales            #+#    #+#             */
/*   Updated: 2023/03/09 17:54:18 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config_parser.hpp"
#include "utils.hpp"
#include <iostream>
#include <cstring>

static bool	parse_token(const std::string& str)
{
	if (str.empty()) return (false);
	size_t	spaces = 0;

	std::cout << str << std::endl;
	spaces = std::strspn(str.c_str(), " \t");
	if (spaces == str.size()) return (false);

	return (true);
}

bool	HttpConfigParser::Parse(const HttpConfig& c)
{
	if (!c.getData() || !c.length()) return (false);

	std::string	str(c.getData());

	size_t	ln = 0;
	size_t	start = 0;

	ln = str.find("\n");

	while (ln != std::string::npos)
	{
		std::cout << parse_token(str.substr(start, ln)) << std::endl;
		start += ln+1;
		ln = str.find("\n", start);
	}

	return (true);
}
