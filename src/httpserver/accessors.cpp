/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accessors.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 01:09:40 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/04 01:11:41 by sam0verfl0w      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_server.hpp"

const std::string&	HttpServer::getAddress(void) const
{
	return (this->_address);
}

const std::string&	HttpServer::getIP(void) const
{
	return (this->_ip);
}

port_t	HttpServer::getPort(void) const
{
	return (this->_port);
}
