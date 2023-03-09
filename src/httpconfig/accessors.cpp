/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accessors.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:44:02 by stales            #+#    #+#             */
/*   Updated: 2023/03/09 17:46:05 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config.hpp"

/*********************************************************************
*
* @brief    Get Server IP configuration
*
* @return   reference to a string which is IP of configuration server 
*
*********************************************************************/
const std::string&	HttpConfig::getIP(void) const
{
	return (this->_ip);
}

/*********************************************************************
*
* @brief    Get Server Port configuration
*
* @return   port_t on unsigned short 0x0-0xFFFF 
*
*********************************************************************/
port_t	HttpConfig::getPort(void) const
{
	return (this->_port);
}
