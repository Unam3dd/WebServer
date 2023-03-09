/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_config_parser.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:50:26 by stales            #+#    #+#             */
/*   Updated: 2023/03/09 19:56:08 by stales           ###   ########.fr       */
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

enum parse_config_status_t
{
	CONFIG_LOADED_SUCCESS,
	CONFIG_LOADED_FAILED
};

/*
 * @class	Http Config Parser
 */
class HttpConfigParser: private HttpConfig
{
	public:
		HttpConfigParser(void);
		HttpConfigParser(const HttpConfigParser& h);
		HttpConfigParser	&operator=(const HttpConfigParser& h);
		~HttpConfigParser(void);

		const std::string		*GetTokensTable(size_t *size) const;
		const std::string&		GetStringToken(config_tokens_t token);
		config_tokens_t			GetTypeToken(const std::string& str);
		parse_config_status_t	Parse(const HttpConfig& c);
		void					PrintConfigurationStatus(parse_config_status_t s);
	
	private:
		int						parse_token(const std::string& str);
		int						read_token(const std::string& str);
		int						read_value(const std::string& str);
};

#endif
