/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserver.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:23:56 by stales            #+#    #+#             */
/*   Updated: 2023/03/15 11:27:42 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include <string>
#include <vector>
#include "http_config.hpp"
#include "http_request_config.hpp"

class WebServer
{
	public:
		WebServer(void);
		WebServer(const std::string& path);
		WebServer(const WebServer& ws);
		WebServer	&operator=(const WebServer& ws);
		~WebServer(void);
	
	private:
		std::vector<HttpServerConfig> _configs;
};

#endif
