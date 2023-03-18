/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserver.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:23:56 by stales            #+#    #+#             */
/*   Updated: 2023/03/18 17:22:36 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#ifndef DEBUG
# define DEBUG 0
#endif

#define COUNT_SPACES(x) (std::count(x.begin(), x.end(), ' ') + std::count(x.begin(), x.end(), '\t'))
#define SANITIZE_SPACES(x) x.erase(std::remove(x.begin(), x.end(), ' '), x.end()); x.erase(std::remove(x.begin(), x.end(), '\t'), x.end())

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

		int								Parse(const std::string& path);
		int								Parse(void);

		inline size_t					GetNumberOfServers(void) const { return (this->_nserv); }
	
	private:
		/*
		 * 	Private members
		 */
		std::vector<HttpServerConfig>	_configs;
		size_t							_nserv;
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
