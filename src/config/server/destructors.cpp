/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:51:56 by stales            #+#    #+#             */
/*   Updated: 2023/03/20 16:20:01 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config.hpp"

HttpServerConfig::~HttpServerConfig(void)
{
	for (std::vector<HttpRequestConfig*>::iterator it = _reqconfig.begin(); it != _reqconfig.end(); it++)
	{
		delete *it;
	}
}
