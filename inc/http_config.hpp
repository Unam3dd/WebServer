/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_config.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:02:25 by stales            #+#    #+#             */
/*   Updated: 2023/04/13 12:59:04 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_CONFIG_HPP
#define HTTP_CONFIG_HPP

#include "file.hpp"
#include "socket.hpp"
#include "http_utils.hpp"
#include "http_request_config.hpp"
#include <vector>
#include <map>
/*********************************************************************
* @brief    HttpServerConfig Class
*********************************************************************/

class HttpServerConfig
{
	public:
		typedef t_errcode (HttpServerConfig::*t_parseMap)(const std::vector<std::string>& argv);

		HttpServerConfig(void);
		HttpServerConfig(const std::string& path);
		HttpServerConfig(const HttpServerConfig& c);
		~HttpServerConfig(void);


		inline const std::vector<HttpRequestConfig*>&		GetRequestConfigs(void) const { return (this->_reqconfig); }
		inline const std::map<std::string, t_parseMap>&		GetParseMap(void) const { return (this->_parseMap); }
		inline const std::map<std::string, std::string>&	GetCgi(void) const { return (this->_cgi); }
		inline std::vector<std::string>&					GetServerNames(void) { return (this->_names); }
		inline const std::vector<std::string>&				GetIndexs(void) const { return (this->_indexs); }
		inline std::vector<port_t>&							GetServerPorts(void) { return (this->_ports); }
		inline const std::vector<redirect_t>&				GetRedirections(void) const { return (this->_redirects); }
		inline const std::string&							GetRoot(void) const { return (this->_root); }
		inline const std::string&							GetIp(void) const { return (this->_ip); }
		inline const std::string&							GetUploadDir(void) const { return (this->_uploaddir); }
		inline const std::string&							GetSessionPath(void) const { return (this->_sessionpath); }
		inline const errpage_t								*GetErrorPages(void) const { return (this->_errpages); }
		inline methods_t									GetMethods(void) const { return (this->_methods); }
		inline maxpost_size_t								GetMaxPostSize(void) const { return (this->_max_size_post); }
		inline bool											GetCookies(void) const { return (this->_cookies); }
		inline bool											GetUploads(void) const { return (this->_uploads); }
		inline bool											GetDirList(void) const { return (this->_dirlist); }

		t_errcode											SetServerNames(const std::vector<std::string>& names);
		t_errcode											SetIndexes(const std::vector<std::string>& indexs);
		t_errcode											SetServerPorts(const std::vector<std::string>& ports);
		t_errcode											SetErrorPages(const std::vector<std::string>& errpages);
		t_errcode											SetRoot(const std::vector<std::string>& root);
		t_errcode											SetSessionPath(const std::vector<std::string>& sessionpath);
		t_errcode											SetMethods(const std::vector<std::string>& methods);
		t_errcode											SetMaxPostSize(const std::vector<std::string>& max_size_post);
		t_errcode											SetCookies(const std::vector<std::string>& cookies);
		t_errcode											SetUploads(const std::vector<std::string>& uploads);
		t_errcode											SetUploadDir(const std::vector<std::string>& uploaddir);
		t_errcode											SetDirList(const std::vector<std::string>& dirlist);
		t_errcode											SetCgi(const std::vector<std::string>& cgi);
		t_errcode											SetRedirect(const std::vector<std::string>& redirect);
		t_errcode											SetIp(const std::vector<std::string>& ip);
	
		void												initNewLocBlk(const std::string& scope) { 
																	this->_reqconfig.push_back(new HttpRequestConfig(scope)); \
																	this->_nreqcfg +=1; }
		friend std::ostream&								operator<<(std::ostream& os, HttpServerConfig& c);

	protected:
		std::map<std::string,t_parseMap>	_parseMap;
		std::map<std::string, std::string>	_cgi;
		std::vector<std::string>			_names;
		std::vector<port_t>					_ports;
		std::vector<HttpRequestConfig*>		_reqconfig;
		std::vector<std::string>			_indexs;
		std::vector<redirect_t>				_redirects;
		errpage_t							_errpages[MAX_ERR_PAGES];
		std::string							_ip;
		std::string							_root;
		std::string							_sessionpath;
		std::string							_uploaddir;
		methods_t							_methods;
		maxpost_size_t						_max_size_post;
		int									_nreqcfg;
		bool								_cookies;
		bool								_uploads;
		bool								_dirlist;
};


#endif
