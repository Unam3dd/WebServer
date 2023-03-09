/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:02:17 by stales            #+#    #+#             */
/*   Updated: 2023/03/09 18:11:32 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config_parser.hpp"
#include "utils.hpp"
#include <iostream>
#include <cstring>

int HttpConfigParser::parse_token(const std::string& str)
{
	if (str.empty()) return (1);
	size_t	spaces = 0;

	spaces = std::strspn(str.c_str(), " \t");
	if (spaces == str.size()) return (1);

	spaces = std::strcspn(str.c_str(), " \t");
	if (spaces == str.size() || !spaces)
		return (1);

	std::cout << this->GetTypeToken(str.substr(0, spaces)) << std::endl;

	return (0);
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
