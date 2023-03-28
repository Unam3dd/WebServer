/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:32:27 by stales            #+#    #+#             */
/*   Updated: 2023/03/28 12:41:23 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "webserver.hpp"
#include <cstdlib>

bool	check_overflow_port(const std::string &str)
{
	if (str.empty()) return (false);

	unsigned long long	_ov = std::atoll(str.c_str());
	unsigned short		_real = _ov;

	return (_ov != _real);
}

WebServer*	SG_WebServer(const WebServer* ws)
{
	static WebServer*	_sg = NULL;

	if (ws)
		_sg = const_cast<WebServer*>(ws);
	return (_sg);
}
