/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:33:12 by stales            #+#    #+#             */
/*   Updated: 2023/03/20 06:08:13 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config.hpp"
#include "webserver.hpp"

WebServer::~WebServer(void)
{
	for (std::vector<HttpServerConfig*>::iterator it = _configs.begin(); it != _configs.end(); it++)
		delete *it;
}
