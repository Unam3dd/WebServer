/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:25:23 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/04 12:55:11 by sam0verfl0w      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config.hpp"
#include "http_colors.hpp"
#include <iostream>

void	HttpConfig::close(void)
{
	if (!_f.is_open())
		return ;
	std::cout << SUCCESS << " " << this->_fname << " correctly closed !" << std::endl;
	_f.close();
}
