/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getconfig.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:17:04 by ldournoi          #+#    #+#             */
/*   Updated: 2023/05/24 17:39:03 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_response.hpp"
#include "logger.hpp"
#include "webserver.hpp"
#include <iostream>

/*
 * @brief: get the server config for the given host and port.
 *
 * @param: host: the host for which to get the server config.
 * @param: port: the port for which to get the server config.
 *
 * @return: the server config for the given host and port.
 * if no server config is found for the host but a server config is found for the
 * port, return the first server cofig matching the port.
 * if no server config is found for the port but a server config is found for the
 * host, return the first server config matching the host.
 * then, if no server config is found for the host and the port, return the first
 * server config of config file.
 *
 */

HttpServerConfig*	HttpResponse::_getSrvConfig(const std::string& host, port_t port){
	std::vector<HttpServerConfig*> srvs = SG_WebServer(NULL)->GetServers();

	FOREACH_VECTOR(HttpServerConfig*, srvs, cfg){
		FOREACH_VECTOR(port_t, (*cfg)->GetServerPorts(), prt){
			FOREACH_VECTOR(std::string, (*cfg)->GetServerNames(), name){
				if (host == *name && port == *prt)
					return (*cfg);
			}
		}
		FOREACH_VECTOR(port_t, (*cfg)->GetServerPorts(), prt){
			if (port == *prt)
				return (*cfg);
		}
		FOREACH_VECTOR(std::string, (*cfg)->GetServerNames(), name){
			if (host == *name)
				return (*cfg);
		}
	}
	return srvs[0];
}

/*
 * @brief: get the request config (or location block) for the given uri.
 *
 * @param: cfg: the server config for which to get the request config.
 * @param: uri: the uri for which to get the request config.
 *
 * @return: the request config for the given uri.
 * if no request config is found for the uri, returns NULL.
 *
 */
HttpRequestConfig* HttpResponse::_getReqConfig(const HttpServerConfig* cfg, const std::string& uri){
	std::vector<HttpRequestConfig*> reqs = cfg->GetRequestConfigs();

	logz.log(L_DEBUG, "uri: " + uri);
	FOREACH_VECTOR(HttpRequestConfig*, reqs, req){
		if (uri.substr(0, (*req)->GetScope().length()) == (*req)->GetScope())
			return (*req);
	}
	return NULL;
}


