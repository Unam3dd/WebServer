/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserver.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:23:56 by stales            #+#    #+#             */
/*   Updated: 2023/03/29 15:21:49 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include "http_server.hpp"
#ifndef DEBUG
# define DEBUG 0
#endif

#include "epoll.hpp"
#include <string>
#include <vector>
#include <map>
#include "file.hpp"
#include "http_utils.hpp"
#include "http_config.hpp"

#define MAX_EVENT 16

class WebServer: public File
{
	public:
		WebServer(void);
		WebServer(const std::string& path);
		WebServer(const WebServer& ws);
		WebServer	&operator=(const WebServer& ws);
		~WebServer(void);

		t_errcode								Parse(void);
		t_status								Run(void);

		inline size_t							GetNumberOfServers(void) const { return (this->_nserv);}
		inline std::vector <HttpServerConfig*>	GetServers(void) const { return (this->_configs); }
		friend std::ostream						&operator<<(std::ostream& os, const WebServer& ws);

		inline const errcodestr_t&				GetErrorStrs(void) const { return (this->_error); }
		inline bool								GetRun(void) const { return (this->_run); }
		inline void								SetRun(bool value) { this->_run = value; }
	
	private:
		/*
		 * 	Private members
		 */
		std::vector<HttpServerConfig*>	_configs;
		std::vector<HttpServer*>		_srv;
		std::vector<Socket*>			_clients;
		Epoll							_epoll;
		errcodestr_t					_error;
		size_t							_nserv;
		int								_line;
		bool							_srvBlk;
		bool							_locBlk;
		bool							_run;
	
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
		t_status						_setupSrvs(void);
		t_status						_listenSrvs(void);
		t_status						_setupEpoll(void);
		t_status						_waitSrvs(void);
		t_status						_acceptClient(ev_t *ev);
};

#endif
