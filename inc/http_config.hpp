/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_config.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:02:25 by stales            #+#    #+#             */
/*   Updated: 2023/03/13 16:43:28 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_CONFIG_HPP
#define HTTP_CONFIG_HPP

#include "file.hpp"
#include "socket.hpp"
#include <vector>

class	HttpRequestConfig
{
	public:
		HttpRequestConfig(void);
		HttpRequestConfig(const HttpRequestConfig& c);
		~HttpRequestConfig(void);
};

class HttpServerConfig: public File
{
	public:
		HttpServerConfig(void);
		HttpServerConfig(const std::string& path);
		HttpServerConfig(const HttpServerConfig& c);
		~HttpServerConfig(void);

		inline const std::string&			GetServerName(void) const { return (this->_name); }
		inline const std::vector<port_t>&	GetServerPort(void) const { return (this->_port); }
		inline unsigned int					GetServerTimeout(void) const { return (this->_timeout); }
	
	private:
		std::string						_name;
		std::string						_root;
		std::vector<HttpRequestConfig>	_reqconfig;
		std::vector<port_t>				_port;
		unsigned int					_timeout;

};


#endif
