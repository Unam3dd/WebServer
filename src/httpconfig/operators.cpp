/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:15:22 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/04 19:16:18 by sam0verfl0w      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.hpp"
#include "http_config.hpp"

HttpConfig &HttpConfig::operator=(const HttpConfig &f)
{
	if (this == &f) return(*this);

	*this = f;
	return (*this);
}
