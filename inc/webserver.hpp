/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserver.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:23:56 by stales            #+#    #+#             */
/*   Updated: 2023/03/17 16:02:32 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#ifndef DEBUG
# define DEBUG 0
#endif

#include <string>
#include <vector>
#include "file.hpp"
#include "http_config.hpp"
#include "http_request_config.hpp"

typedef enum {
	ERRPARSE_OK = 0,
	ERRPARSE_NEWSRVBLK,
	ERRPARSE_NEWLOCBLK,
	ERRPARSE_ENDBLK
} t_errcode;

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
		/*
		 * 	Private members
		 */
		std::vector<HttpServerConfig>	_configs;
		size_t							_nserv;

		/*
		 * 	Private methods
		 */
		t_errcode		_parseSrvBlk(const std::string& line);
		t_errcode		_parseLocBlk(const std::string& line);
		bool			_isSrvBlk(const std::string& line);
		bool			_isLocBlk(const std::string& line);
		bool			_isEndBlk(const std::string& line);
};

#endif
