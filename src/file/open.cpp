/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:32:22 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/04 18:38:28 by sam0verfl0w      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.hpp"
#include "http_colors.hpp"
#include <sys/stat.h>
#include <iostream>

bool	File::open(const char *filename, int flags, mode_t mode)
{
	struct stat	s;

	if (!filename) {
		std::cerr << FAIL << " filename is empty !" << std::endl;
		return (false);
	}

	if (stat(filename, &s) < 0) {
		std::cerr << FAIL << " to execute stat on " << filename << std::endl;
		return (false);
	}

	if (s.st_mode & S_IFDIR) {
		std::cerr << FAIL << " " << filename << " is a directory/folder !" << std::endl;
		return (false);
	}

	_fd = ::open(filename, flags, mode);

	if (_fd < 0) {
		std::cerr << FAIL << " opening " << filename << " due an a error permissions !" << std::endl;
		return (false);
	}

	std::cout << SUCCESS << " " << filename << " was opened successfully !" << std::endl;
	_filename = const_cast<char *>(filename);
	return (true);
}
