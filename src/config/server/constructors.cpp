/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:48:26 by stales            #+#    #+#             */
/*   Updated: 2023/03/13 19:16:15 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.hpp"
#include "http_config.hpp"

HttpServerConfig::HttpServerConfig(void): File()
{
}

HttpServerConfig::HttpServerConfig(const std::string& path): File(path.c_str(), O_RDONLY, S_IRUSR)
{
	(void)path;
	this->Parse(path);
}

HttpServerConfig::HttpServerConfig(const HttpServerConfig& c): File(c)
{
	if (this == &c) return ;

	*this = c;
}

