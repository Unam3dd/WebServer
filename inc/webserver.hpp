/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserver.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:23:56 by stales            #+#    #+#             */
/*   Updated: 2023/03/23 12:04:48 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#ifndef DEBUG
# define DEBUG 0
#endif

#include <string>
#include <vector>
#include <map>
#include "file.hpp"
#include "http_utils.hpp"
#include "http_config.hpp"

class WebServer: public File
{
	public:
		WebServer(void);
		WebServer(const std::string& path);
		WebServer(const WebServer& ws);
		WebServer	&operator=(const WebServer& ws);
		~WebServer(void);

		t_errcode						Parse(void);

		inline size_t					GetNumberOfServers(void) const { return (this->_nserv);}
		inline std::vector < HttpServerConfig* >	GetServers(void) const { return (this->_configs); }
		friend std::ostream				&operator<<(std::ostream& os, const WebServer& ws);

		inline const errcodestr_t&					GetErrorStrs(void) const { return (this->_error); }
	
	private:
		/*
		 * 	Private members
		 */
		std::vector<HttpServerConfig*>	_configs;
		errcodestr_t					_error;
		size_t							_nserv;
		int								_line;
		bool							_srvBlk;
		bool							_locBlk;
	
		/*
		 * 	Private methods
		 */
		std::vector<std::string>		_splitDirective(const std::string& line);
		t_errcode						_parseSrvDirective(const std::string& line);
		t_errcode						_parseLocDirective(const std::string& line);
		bool							_isSrvBlk(const std::string& line);
		bool							_isLocBlk(const std::string& line);
		bool							_isEndBlk(const std::string& line);
		void							_initNewSrvBlk(void);
		t_errcode						_initNewLocBlk(const std::string& line);
};

#endif
