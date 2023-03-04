/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:40:32 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/04 18:44:13 by sam0verfl0w      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.hpp"
#include "http_colors.hpp"
#include <iostream>
#include <unistd.h>

void	File::close(void)
{
	if (_fd < 0) return ;
	::close(_fd);
	std::cout << SUCCESS << " " << _filename << " closed successfully !" << std::endl;
	_fd = -1;
}
