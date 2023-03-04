/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 13:10:43 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/04 15:07:16 by sam0verfl0w      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config.hpp"
#include <cstring>
#include <ios>
#include <iostream>
#include <stddef.h>

size_t	HttpConfig::read(void)
{
	size_t	len = 0;

	if (!_f.is_open()) return (0);

	_f.seekg(0, std::ios::end);
	len = _f.tellg();
	_f.seekg(0, std::ios::beg);

	_data.reserve(len);
	std::memset(const_cast<char*>(_data.c_str()), 0, len);

	_f.read(const_cast<char*>(_data.c_str()), _data.capacity());

	return (_data.length());
}
