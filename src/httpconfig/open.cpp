/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:22:45 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/04 13:02:02 by sam0verfl0w      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config.hpp"
#include "http_colors.hpp"
#include <iostream>
#include <sys/stat.h>

bool	HttpConfig::open(const std::string &filename)
{
	struct stat	s;

	// Check If filename is empty
	if (filename.empty()) {
		std::cerr << FAIL << " Filename is empty !" << std::endl;
		return (false);
	}

	// Make Stat system call request to get information about filename
	if (stat(filename.c_str(), &s) < 0) {
		std::cerr << FAIL << " " << filename << " error during stat system call !" << std::endl;
		return (false);
	}

	// If filename is a directory then return false
	if (s.st_mode & S_IFDIR) {
		std::cerr << FAIL << " " << filename << " is a directory/folder !" << std::endl;
		return (false); 
	}

	// Open file
	this->_f.open(filename.c_str(), std::ios::in);

	// check if file is correctly opened !
	if (!_f.is_open()) {
		std::cerr << FAIL << " to open due bad permissions" << filename << " !" << std::endl;
		return (false);
	}

	std::cout << SUCCESS << " " << filename << " was opened !" <<  std::endl;
	_fname = filename;
	return (true);
}
