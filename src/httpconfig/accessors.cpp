/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accessors.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 13:05:57 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/04 14:44:37 by sam0verfl0w      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config.hpp"

const std::string&	HttpConfig::getFilename(void) const
{
	return (this->_fname);
}

const std::string&	HttpConfig::getData(void) const
{
	return (_data);
}
