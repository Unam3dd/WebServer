/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:47:54 by stales            #+#    #+#             */
/*   Updated: 2023/03/08 01:36:56 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_server.hpp"
#include "http_utils.hpp"
#include <netinet/in.h>

HttpServer::HttpServer(void): _port(0) {}

HttpServer::HttpServer(const std::string& ip, port_t port)
{
	(ip.empty() || (IS_BAD_IP(ip)) ? _ip = "0.0.0.0" : _ip = ip);
	_port = port;
	_s.SetupSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	_s.SetupSin(AF_INET, this->_ip, this->_port);
	_s.Bind();
}

HttpServer::HttpServer(const HttpServer& h)
{
	if (this == &h) return ;
	*this = h;
}
