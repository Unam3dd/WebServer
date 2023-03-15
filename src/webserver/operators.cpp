/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:33:30 by stales            #+#    #+#             */
/*   Updated: 2023/03/15 11:34:19 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserver.hpp"

WebServer	&WebServer::operator=(const WebServer& ws)
{
	if (this == &ws) return (*this);
	*this = ws;
	return (*this);
}
