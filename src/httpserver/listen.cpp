/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:13:50 by stales            #+#    #+#             */
/*   Updated: 2023/03/26 14:43:45 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_server.hpp"
#include "logger.hpp"
#include <iostream>

/*********************************************************************
*
* @brief    Listening on port
*
* @param	int:	backlog
*
* @return   true or false
*
*********************************************************************/

bool	HttpServer::Listen(int backlog)
{
	_s.Listen(backlog);
	if (!_s.isOnListening())
		return (false);

	if (!_ip.empty())
		logz.log(L_PASS | L_BYPASS, "Listening on " + this->_ip + ":" + logz.itoa(this->_port) + "/");

	if (this->_ip.empty())
		logz.log(L_PASS | L_BYPASS, "Listening on " + logz.itoa(this->_port) + "/");

	return (true);
}
