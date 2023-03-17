/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:28:25 by ldournoi          #+#    #+#             */
/*   Updated: 2023/03/17 15:29:28 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserver.hpp"
#include <iostream>

t_errcode WebServer::_parseSrvBlk(const std::string& line)
{
	(void)line;
	return (ERRPARSE_OK);
}

t_errcode WebServer::_parseLocBlk(const std::string& line)
{
	(void)line;
	return (ERRPARSE_OK);
}
