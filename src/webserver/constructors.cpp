/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:31:17 by stales            #+#    #+#             */
/*   Updated: 2023/03/15 11:34:33 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserver.hpp"

WebServer::WebServer(void)
{
}

WebServer::WebServer(const std::string& path)
{
	if (path.empty()) return ;
}

WebServer::WebServer(const WebServer& ws)
{
	if (this == &ws) return ;
}

