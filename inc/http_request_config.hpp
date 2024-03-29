/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_request_config.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:17:45 by stales            #+#    #+#             */
/*   Updated: 2023/04/22 19:42:59 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST_CONFIG_HPP
#define HTTP_REQUEST_CONFIG_HPP

#include "socket.hpp"
#include "http_utils.hpp"
#include <vector>
#include <map>

class HttpRequestConfig{
	public:
		typedef t_errcode (HttpRequestConfig::*t_parseMap)(const std::vector<std::string>& argv);
		
		HttpRequestConfig(const std::string& scope);
		HttpRequestConfig(const HttpRequestConfig& c);
		~HttpRequestConfig(void);

		inline const std::map<std::string, t_parseMap>&	GetParseMap(void) const { return (this->_parseMap); }
		inline const std::map<std::string, std::string>& GetCgi(void) const { return (this->_cgi); }
		inline const std::vector<std::string>&			GetIndexs(void) const { return (this->_indexs); }
		inline const errpage_t							*GetErrorPages(void) const { return (this->_errpages); }
		inline const std::string&						GetRoot(void) const { return (this->_root); }
		inline const std::string&						GetScope(void) const { return (this->_scope); }
		inline methods_t								GetMethods(void) const { return (this->_methods); }
		inline maxpost_size_t							GetMaxPostSize(void) const { return (this->_max_size_post); }
		inline bool										GetCookies(void) const { return (this->_cookies); }
		inline bool										GetUploads(void) const { return (this->_uploads); }
		inline bool										GetDirList(void) const { return (this->_dirlist); }
		inline int										GetHttpResponseCode(void) const { return (this->_response_code); }


		t_errcode										SetHttpResponseCode(const std::vector<std::string>& argv);
		t_errcode										SetIndexes(const std::vector<std::string>& indexs);
		t_errcode										SetScope(const std::vector<std::string>& scope);
		t_errcode										SetErrorPages(const std::vector<std::string>& errpages);
		t_errcode										SetRoot(const std::vector<std::string>& root);
		t_errcode										SetMethods(const std::vector<std::string>& methods);
		t_errcode										SetMaxPostSize(const std::vector<std::string>& max_size_post);
		t_errcode										SetCookies(const std::vector<std::string>& cookies);
		t_errcode										SetUploads(const std::vector<std::string>& uploads);
		t_errcode										SetDirList(const std::vector<std::string>& dirlist);
		t_errcode										SetCgi(const std::vector<std::string>& cgi);

		friend std::ostream&							operator<<(std::ostream& os, HttpRequestConfig& c);
	protected:
		std::map<std::string,t_parseMap>	_parseMap;
		std::map<std::string, std::string>	_cgi;
		std::vector<std::string>			_indexs;
		errpage_t							_errpages[MAX_ERR_PAGES];
		std::string							_scope;
		std::string							_root;
		methods_t							_methods;
		maxpost_size_t						_max_size_post;
		int									_response_code;
		bool								_cookies;
		bool								_uploads;
		bool								_dirlist;
};

#endif
