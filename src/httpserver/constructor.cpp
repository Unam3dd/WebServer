/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:47:54 by stales            #+#    #+#             */
/*   Updated: 2023/03/03 12:36:04 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_server.hpp"

HttpServer::HttpServer(void) {}

HttpServer::HttpServer(const std::string& address)
{
	if (address.empty())
		return ;
}

HttpServer::HttpServer(const std::string& ip, port_t port)
{
	(ip.empty() ? _address = "0.0.0.0" : _address = ip);
	_port = port;
}

HttpServer::HttpServer(const HttpServer& h)
{
	if (this == &h)
		return ;
	*this = h;
}
