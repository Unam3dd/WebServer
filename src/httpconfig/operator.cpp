/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 02:14:23 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/04 02:14:29 by sam0verfl0w      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config.hpp"

HttpConfig	&HttpConfig::operator=(const HttpConfig &c)
{
	if (this == &c) return (*this);
	*this = c;
	return (*this);
}
