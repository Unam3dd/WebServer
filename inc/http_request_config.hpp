/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_request_config.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:17:45 by stales            #+#    #+#             */
/*   Updated: 2023/03/15 20:05:30 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST_CONFIG_HPP
#define HTTP_REQUEST_CONFIG_HPP

#include "http_utils.hpp"
#include "http_server.hpp"
#include <vector>

class HttpRequestConfig
{
	public:
		HttpRequestConfig(void);
		HttpRequestConfig(const HttpRequestConfig& c);
		~HttpRequestConfig(void);

		inline const std::vector<HttpRequestConfig>	GetRequestConfigs(void) const { return (this->_reqconfig); }
		inline const std::vector<std::string>		GetIndexs(void) const { return (this->_indexs); }
		inline const errpage_t						*GetErrorPages(void) const { return (this->_errpages); }
		inline const std::string					GetRoot(void) const { return (this->_root); }
		inline const std::string					GetScope(void) const { return (this->_scope); }
		inline const std::string					GetSessionPath(void) const { return (this->_sessionpath); }
		inline timeout_t							GetServerTimeout(void) const { return (this->_timeout); }
		methods_t									GetMethods(void) const { return (this->_methods); }
		maxpost_size_t								GetMaxPostSize(void) const { return (this->_max_size_post); }
		inline bool									GetCookies(void) const { return (this->_cookies); }
		inline bool									GetUploads(void) const { return (this->_uploads); }
		inline bool									GetDirList(void) const { return (this->_dirlist); }

	
	protected:
		std::vector<HttpRequestConfig>	_reqconfig;
		std::vector<std::string>		_indexs;
		errpage_t						_errpages[MAX_ERR_PAGES];
		std::string						_scope;
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
