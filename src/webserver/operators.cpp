/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:33:30 by stales            #+#    #+#             */
/*   Updated: 2023/03/20 00:34:34 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config.hpp"
#include "webserver.hpp"

WebServer	&WebServer::operator=(const WebServer& ws)
{
	if (this == &ws) return (*this);
	*this = ws;
	return (*this);
}

std::ostream	&operator<<(std::ostream& os, const WebServer& ws)
{
	std::vector<HttpServerConfig*> servers = ws.GetServers();
	os << "Number of servers: " << ws.GetNumberOfServers() << std::endl;
	for (size_t i = 0; i < ws.GetNumberOfServers(); i++)
		os << "\t" << *servers.at(i) << std::endl;
	return (os);
}
