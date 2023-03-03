/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:51:13 by stales            #+#    #+#             */
/*   Updated: 2023/03/03 12:36:15 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_server.hpp"

HttpServer	&HttpServer::operator=(const HttpServer &h)
{
	return ((this == &h) ? (*this) : (*this = h, *this));
}
