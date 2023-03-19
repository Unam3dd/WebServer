/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:31:17 by stales            #+#    #+#             */
/*   Updated: 2023/03/15 12:40:28 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserver.hpp"

WebServer::WebServer(void)
{
	_srvBlk = false;
	_locBlk = false;
	_nserv = 0;
}

WebServer::WebServer(const std::string& path): File(path.c_str(), O_RDONLY, S_IRUSR)
{
	if (path.empty()) return ;
	_srvBlk = false;
	_locBlk = false;
	_nserv = 0;
}

WebServer::WebServer(const WebServer& ws): File(ws)
{
	if (this == &ws) return ;
	_srvBlk = false;
	_locBlk = false;
	_nserv = 0;
}

