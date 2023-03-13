/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_config.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:02:25 by stales            #+#    #+#             */
/*   Updated: 2023/03/13 19:14:19 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_CONFIG_HPP
#define HTTP_CONFIG_HPP

#include "file.hpp"
#include "socket.hpp"
#include "http_utils.hpp"
#include "http_request_config.hpp"
#include <vector>

/*********************************************************************
* @brief    HttpServerConfig Class
*********************************************************************/

class HttpServerConfig: public File
{
	public:
		HttpServerConfig(void);
		HttpServerConfig(const std::string& path);
		HttpServerConfig(const HttpServerConfig& c);
		~HttpServerConfig(void);
		
		/*********************************************************************
		*
		* @brief    This function will parse the server config
		*
		* @param   reference on const std::string 
		*
		* @return   0 is success otherwise considered as an error 
		*
		*********************************************************************/
		int											Parse(const std::string& path);
		int											Parse(void);

		inline const std::vector<std::string>&		GetServerName(void) const { return (this->_names); }
		inline const std::vector<HttpRequestConfig>	GetRequestConfig(void) const { return (this->_reqconfig); }
		inline const std::vector<std::string>		GetIndexs(void) const { return (this->_indexs); }
		inline const std::vector<port_t>&			GetServerPort(void) const { return (this->_ports); }
		inline const errpage_t						*GetErrorPages(void) const { return (this->_errpages); }
		inline const std::string					GetRoot(void) const { return (this->_root); }
		inline const std::string					GetSessionPath(void) const { return (this->_sessionpath); }
		inline timeout_t							GetServerTimeout(void) const { return (this->_timeout); }
		methods_t									GetMethods(void) const { return (this->_methods); }
		maxpost_size_t								GetMaxPostSize(void) const { return (this->_max_size_post); }
		inline bool									GetCookies(void) const { return (this->_cookies); }
		inline bool									GetUploads(void) const { return (this->_uploads); }
		inline bool									GetDirList(void) const { return (this->_dirlist); }

	
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
		maxpost_size_t					_max_size_post;
		bool							_cookies;
		bool							_uploads;
		bool							_dirlist;
};


#endif
