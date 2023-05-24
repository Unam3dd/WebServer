/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:48:26 by stales            #+#    #+#             */
/*   Updated: 2023/05/24 02:42:58 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config.hpp"

HttpServerConfig::HttpServerConfig(void)
{
	_parseMap["server_name"] = &HttpServerConfig::SetServerNames;
	_parseMap["server_names"] = &HttpServerConfig::SetServerNames;
	_parseMap["listen"] = &HttpServerConfig::SetServerPorts;
	_parseMap["index"] = &HttpServerConfig::SetIndexes;
	_parseMap["errpage"] = &HttpServerConfig::SetErrorPages;
	_parseMap["docroot"] = &HttpServerConfig::SetRoot;
	_parseMap["max_post_size"] = &HttpServerConfig::SetMaxPostSize;
	_parseMap["cookies"] = &HttpServerConfig::SetCookies;
	_parseMap["uploads"] = &HttpServerConfig::SetUploads;
	_parseMap["dirlist"] = &HttpServerConfig::SetDirList;
	_parseMap["cgi"] = &HttpServerConfig::SetCgi;
	_parseMap["methods"] = &HttpServerConfig::SetMethods;

	_root = "/var/www/html";
	_methods = static_cast<methods_t>(GET | POST | PUT | DELETE);
	_max_size_post = 1000000;
	_cookies = true;
	_uploads = true;
	_dirlist = true;
	_errpages[E400].code = 400;
	_errpages[E400].path = "default";
	_errpages[E401].code = 401;
	_errpages[E401].path = "default";
	_errpages[E403].code = 403;
	_errpages[E403].path = "default";
	_errpages[E404].code = 404;
	_errpages[E404].path = "default";
	_errpages[E405].code = 405;
	_errpages[E405].path = "default";
	_errpages[E408].code = 408;
	_errpages[E408].path = "default";
	_errpages[E411].code = 411;
	_errpages[E411].path = "default";
	_errpages[E500].code = 500;
	_errpages[E500].path = "default";
	_errpages[E501].code = 501;
	_errpages[E501].path = "default";
	_errpages[E502].code = 502;
	_errpages[E502].path = "default";
	_errpages[E505].code = 505;
	_errpages[E505].path = "default";
}

HttpServerConfig::HttpServerConfig(const std::string& path)
{
	(void)path;
}

HttpServerConfig::HttpServerConfig(const HttpServerConfig& c)
{
	if (this == &c) return ;

	*this = c;
}

