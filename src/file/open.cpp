/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:32:22 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/05/24 13:27:03 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.hpp"
#include "http_colors.hpp"
#include "http_utils.hpp"
#include "http_status.hpp"
#include <sys/stat.h>
#include <iostream>

bool	File::open(const char *filename, int flags, mode_t mode)
{
	struct stat	s;

	if (!filename) {
		std::cerr << FAIL << "[File::open()] filename is empty !" << std::endl;
		return (false);
	}

	if (stat(filename, &s) < 0) {
		std::cerr << FAIL << "[File::open()] to execute stat on " << filename << std::endl;
		return (false);
	}

	if (s.st_mode & S_IFDIR) {
		std::cerr << FAIL << "[File::open()] " << filename << " is a directory/folder !" << std::endl;
		return (false);
	}

	_fd = ::open(filename, flags, mode);

	if (_fd < 0) {
		std::cerr << FAIL << " [File::open()] opening " << filename << " failed due to a permission error !" << std::endl;
		return (false);
	}

	std::cout << SUCCESS << "[File::open()] " << filename << " was opened successfully !" << std::endl;
	_filename = const_cast<char *>(filename);
	return (true);
}

http_status_code_t	File::open(const char *filename, mode_t mode){
	struct stat s;

	if (!filename) {
			#if DEBUG==1
			std::cerr << WARN << "[File::open()] filename is empty !" << std::endl;
			#endif
		return (HTTP_STATUS_NOT_FOUND);
	}

	if (stat(filename, &s) < 0) {
			#if DEBUG==1
			std::cerr << WARN << "[File::open()] to execute stat on " << filename << std::endl;
			#endif
		return (HTTP_STATUS_NOT_FOUND);
	}

	if (s.st_mode & S_IFDIR) {
			#if DEBUG==1
			std::cerr << WARN << "[File::open] '" << filename << "' is a directory/folder ! Populating directory list" << std::endl;
			#endif
		_dir = new Directory(filename);
		return (HTTP_STATUS_OK);
	}

	_fd = ::open(filename, O_RDONLY, mode);

	if (_fd < 0) {
			#if DEBUG==1
			std::cerr << WARN << "[File::open()] opening " << filename << " failed due to error permissions !" << std::endl;
			#endif
		return (HTTP_STATUS_FORBIDDEN);
	}
		#if DEBUG==1
		std::cout << SUCCESS << "[File::open()] " << filename << " was opened successfully !" << std::endl;
		#endif
	_filename = const_cast<char *>(filename);
	return (HTTP_STATUS_OK);
}
