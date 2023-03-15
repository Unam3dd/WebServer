/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserver.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:23:56 by stales            #+#    #+#             */
/*   Updated: 2023/03/15 13:07:51 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include <string>
#include <vector>
#include "file.hpp"
#include "http_config.hpp"
#include "http_request_config.hpp"

class WebServer: public File
{
	public:
		WebServer(void);
		WebServer(const std::string& path);
		WebServer(const WebServer& ws);
		WebServer	&operator=(const WebServer& ws);
		~WebServer(void);

		int				Parse(const std::string& path);
		int				Parse(void);

		inline size_t	GetNumberOfServers(void) const { return (this->_nserv); }
	
	private:
		std::vector<HttpServerConfig>	_configs;
		size_t							_nserv;
};

#endif
