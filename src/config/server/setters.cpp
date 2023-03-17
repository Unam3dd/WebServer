/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:57:36 by ldournoi          #+#    #+#             */
/*   Updated: 2023/03/17 19:55:59 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config.hpp"
#include "utils.hpp"
#include "webserver.hpp"
#include <cstdlib>

t_errcode	HttpServerConfig::SetServerNames(const std::vector<std::string> &names)
{
	this->_names = names;
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetIndexes(const std::vector<std::string> &indexs)
{
	this->_indexs = indexs;
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetServerPorts(const std::vector<std::string> &ports)
{
	int port = 0;

	for (std::vector<std::string>::const_iterator it = ports.begin(); it != ports.end(); it++)
	{
		if (check_overflow_port(*it))
			return (ERRPARSE_PORT);
		port = std::atoi(it->c_str());
		if (port <= 0 || port > 65535)
			return (ERRPARSE_PORT);
		this->_ports.push_back(static_cast<port_t>(port));
	}
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetErrorPages(const std::vector<std::string> &pages)
{
	if (pages.at(0) == "errpage400")
	{
		this->_errpages[E400].code = 400;
		this->_errpages[E400].path = pages.at(1);
	}
	else if (pages.at(0) == "errpage401")
	{
		this->_errpages[E401].code = 401;
		this->_errpages[E401].path = pages.at(1);
	}
	else if (pages.at(0) == "errpage403")
	{
		this->_errpages[E403].code = 403;
		this->_errpages[E403].path = pages.at(1);
	}
	else if (pages.at(0) == "errpage404")
	{
		this->_errpages[E404].code = 404;
		this->_errpages[E404].path = pages.at(1);
	}
	else if (pages.at(0) == "errpage405")
	{
		this->_errpages[E405].code = 405;
		this->_errpages[E405].path = pages.at(1);
	}
	else if (pages.at(0) == "errpage500")
	{
		this->_errpages[E500].code = 500;
		this->_errpages[E500].path = pages.at(1);
	}
	else if (pages.at(0) == "errpage501")
	{
		this->_errpages[E501].code = 501;
		this->_errpages[E501].path = pages.at(1);
	}
	else if (pages.at(0) == "errpage505")
	{
		this->_errpages[E505].code = 505;
		this->_errpages[E505].path = pages.at(1);
	}
	return (ERRPARSE_ERRPAGE);
}

t_errcode	HttpServerConfig::SetRoot(const std::string &root)
{
	this->_root = root;
	return (ERRPARSE_OK);
}

t_errcode	HttpServerConfig::SetMaxPostSize(const std::string &max_size_post)
{
	//if (check_overflow_size(max_size_post))
	//	return (ERRPARSE_MAXPOSTSIZE);
	this->_max_size_post = std::atoi(max_size_post.c_str());
	return (ERRPARSE_OK);
}
