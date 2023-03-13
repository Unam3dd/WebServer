/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_config.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:02:25 by stales            #+#    #+#             */
/*   Updated: 2023/03/13 17:37:25 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_CONFIG_HPP
#define HTTP_CONFIG_HPP

#include "file.hpp"
#include "socket.hpp"
#include "http_utils.hpp"
#include <vector>

class HttpRequestConfig;

class HttpServerConfig: public File
{
	public:
		HttpServerConfig(void);
		HttpServerConfig(const std::string& path);
		HttpServerConfig(const HttpServerConfig& c);
		~HttpServerConfig(void);

		inline const std::vector<std::string>&		GetServerName(void) const { return (this->_names); }
		inline const std::vector<port_t>&			GetServerPort(void) const { return (this->_ports); }
		inline timeout_t							GetServerTimeout(void) const { return (this->_timeout); }
	
	protected:
		std::vector<std::string>		_names;
		std::vector<port_t>				_ports;
		std::vector<HttpRequestConfig>	_reqconfig;
		std::vector<std::string>		_indexs;
		errpage_t						_errpages[MAX_ERR_PAGES];
		std::string						_root;
		std::string						_sessionpath;
		methods_t						_methods;
		timeout_t						_timeout;
		bool							_cookies;
		bool							_uploads;
};


#endif
