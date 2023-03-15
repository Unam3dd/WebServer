/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:48:26 by stales            #+#    #+#             */
/*   Updated: 2023/03/15 11:19:36 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.hpp"
#include "http_config.hpp"

HttpServerConfig::HttpServerConfig(void)
{
}

HttpServerConfig::HttpServerConfig(const std::string& path)
{
	(void)path;
}

HttpServerConfig::HttpServerConfig(const HttpServerConfig& c)
{
	if (this == &c) return ;

	*this = c;
}
