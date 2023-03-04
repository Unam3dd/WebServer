/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:40:32 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/04 15:43:12 by sam0verfl0w      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.hpp"
#include "http_colors.hpp"
#include <iostream>
#include <unistd.h>

bool	File::close(void)
{
	if (::close(_fd) < 0) {
		std::cerr << FAIL << " error during closing " << _filename << std::endl;
		return (false);
	}
	std::cout << SUCCESS << " " << _filename << " closed successfully !" << std::endl;
	return (true);
}
