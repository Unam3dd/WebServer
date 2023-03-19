/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:33:30 by stales            #+#    #+#             */
/*   Updated: 2023/03/19 09:42:28 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserver.hpp"

WebServer	&WebServer::operator=(const WebServer& ws)
{
	if (this == &ws) return (*this);
	*this = ws;
	return (*this);
}

std::ostream	&operator<<(std::ostream& os, const WebServer& ws)
{
	std::vector < HttpServerConfig > serverConfigs = ws.GetServers();

	os << "Number of servers: " << ws._nserv << std::endl;
	for (size_t i = 0; i < serverConfigs.size(); i++)
		os << "\t" << serverConfigs[i];
	return (os);
}
