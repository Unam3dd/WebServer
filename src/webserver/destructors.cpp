/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:33:12 by stales            #+#    #+#             */
/*   Updated: 2023/03/25 20:55:25 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config.hpp"
#include "http_request_config.hpp"
#include "http_server.hpp"
#include "webserver.hpp"

WebServer::~WebServer(void)
{
	for (std::vector<HttpServerConfig*>::iterator it = _configs.begin(); it != _configs.end(); it++)
	{
		delete *it;
	}

	for (std::vector<HttpServer*>::iterator it = _srv.begin(); it != _srv.end(); it++)
	{
		delete *it;
	}
}
