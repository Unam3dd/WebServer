/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:47:54 by stales            #+#    #+#             */
/*   Updated: 2023/03/28 14:50:51 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_server.hpp"
#include "http_utils.hpp"
#include "http_colors.hpp"
#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <iostream>

HttpServer::HttpServer(void): _port(0) {}

HttpServer::HttpServer(const std::string& ip, port_t port)
{
	int opt = 1;

	(ip.empty() || (IS_BAD_IP(ip)) ? _ip = "0.0.0.0" : _ip = ip);
	_port = port;
	_s.SetupSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	_s.SetSockOpt(this->_s.Getfd(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	_s.SetupSin(AF_INET, this->_ip, this->_port);
	if (_s.Bind() == -1)
		throw std::runtime_error("");
}

HttpServer::HttpServer(const HttpServer& h)
{
	if (this == &h) return ;
	*this = h;
}
