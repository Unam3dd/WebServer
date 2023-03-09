/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:04:09 by stales            #+#    #+#             */
/*   Updated: 2023/03/09 19:00:49 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config_parser.hpp"
#include <iostream>

const std::string	*HttpConfigParser::GetTokensTable(size_t *size) const
{
	static const std::string tokens[3] = { "", "ADDR", "PORT" };

	if (size)
		*size = sizeof(tokens)/sizeof(std::string);
	return (tokens);
}

const std::string&	HttpConfigParser::GetStringToken(config_tokens_t token)
{
	return (this->GetTokensTable(NULL)[token]);
}

config_tokens_t	HttpConfigParser::GetTypeToken(const std::string& str)
{
	size_t	size = 0;
	const std::string *tok = this->GetTokensTable(&size);

	if (str.empty()) return (CONFIG_TOKEN_INVALID);

	for (size_t i = 0; i < size; i++)
		if (str == tok[i]) return ((config_tokens_t)i);

	return (CONFIG_TOKEN_INVALID);
}
