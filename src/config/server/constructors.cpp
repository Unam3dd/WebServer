/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:48:26 by stales            #+#    #+#             */
/*   Updated: 2023/03/18 16:45:32 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.hpp"
#include "http_config.hpp"

HttpServerConfig::HttpServerConfig(void)
{
	_parseMap["server_name"] = &HttpServerConfig::SetServerNames;
	_parseMap["server_names"] = &HttpServerConfig::SetServerNames;
	_parseMap["listen"] = &HttpServerConfig::SetServerPorts;
	_parseMap["index"] = &HttpServerConfig::SetIndexes;
	_parseMap["errpage"] = &HttpServerConfig::SetErrorPages;
	_parseMap["docroot"] = &HttpServerConfig::SetRoot;
	_parseMap["session_path"] = &HttpServerConfig::SetSessionPath;
	_parseMap["timeout"] = &HttpServerConfig::SetServerTimeout;
	_parseMap["max_post_size"] = &HttpServerConfig::SetMaxPostSize;
	_parseMap["cookies"] = &HttpServerConfig::SetCookies;
	_parseMap["uploads"] = &HttpServerConfig::SetUploads;
	_parseMap["upload_dir"] = &HttpServerConfig::SetUploadDir;
	_parseMap["dirlist"] = &HttpServerConfig::SetDirList;
	_parseMap["cgi"] = &HttpServerConfig::SetCgi;
	_parseMap["methods"] = &HttpServerConfig::SetMethods;
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

