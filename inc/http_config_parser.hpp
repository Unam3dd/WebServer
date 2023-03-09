/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_config_parser.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:50:26 by stales            #+#    #+#             */
/*   Updated: 2023/03/09 18:09:18 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef HTTP_CONFIG_PARSER_HPP
#define HTTP_CONFIG_PARSER_HPP

#include "http_config.hpp"
#include <string>

/*
 *	Configurations Tokens
 */
enum config_tokens_t
{
	CONFIG_TOKEN_INVALID	= 0,
	CONFIG_TOKEN_ADDR		= 1 << 0,
	CONFIG_TOKEN_PORT		= 1 << 1
};

/*
 * @class	Http Config Parser
 */
class HttpConfigParser: private HttpConfig
{
	public:
		HttpConfigParser(void);
		HttpConfigParser(const HttpConfig& c);
		HttpConfigParser(const HttpConfigParser& h);
		HttpConfigParser	&operator=(const HttpConfigParser& h);
		~HttpConfigParser(void);

		config_tokens_t	GetTypeToken(const std::string& str);
		bool			Parse(const HttpConfig& c);
	
	private:
		int				parse_token(const std::string& str);
};

#endif
