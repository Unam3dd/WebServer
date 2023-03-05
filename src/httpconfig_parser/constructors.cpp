/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:58:42 by stales            #+#    #+#             */
/*   Updated: 2023/03/05 16:00:14 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config_parser.hpp"

HttpConfigParser::HttpConfigParser(void)
{
}

HttpConfigParser::HttpConfigParser(const HttpConfigParser& h)
{
	(void)h;
}

HttpConfigParser::HttpConfigParser(const HttpConfig& c)
{
	(void)c;
}

