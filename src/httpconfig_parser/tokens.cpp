/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:04:09 by stales            #+#    #+#             */
/*   Updated: 2023/03/09 18:12:27 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config_parser.hpp"

config_tokens_t	HttpConfigParser::GetTypeToken(const std::string& str)
{
	static const std::string tok[3] = { "", "ADDR", "PORT" };

	if (str.empty()) return (CONFIG_TOKEN_INVALID);

	for (size_t i = 0; i < sizeof(tok)/sizeof(std::string); i++)
		if (str == tok[i]) return ((config_tokens_t)i);

	return (CONFIG_TOKEN_INVALID);
}
