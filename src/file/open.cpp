/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:32:22 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/05/27 09:58:32 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.hpp"
#include "logger.hpp"
#include "http_utils.hpp"
#include "http_status.hpp"
#include <sys/stat.h>
#include <iostream>

bool	File::open(const char *filename, int flags, mode_t mode)
{
	struct stat	s;
	std::string	tmp_filename(filename);

	if (!filename) {
		logz.logerr(L_WARN, "file name is empty !");
		return (false);
	}

	if (stat(filename, &s) < 0) {
		logz.logerr(L_WARN, "to execute stat on " + tmp_filename);
		return (false);
	}

	if (s.st_mode & S_IFDIR) {
		logz.logerr(L_WARN, tmp_filename + " is a directory/folder !");
		return (false);
	}

	_fd = ::open(filename, flags, mode);

	if (_fd < 0) {
		logz.log(L_WARN, "opening " + tmp_filename + " failed due to a permission error !");
		return (false);
	}
	logz.log(L_PASS, tmp_filename + " was opened successfully !");
	_filename = const_cast<char *>(filename);
	return (true);
}

http_status_code_t	File::open(const char *filename, mode_t mode)
{
	struct stat s;
	std::string tmp_filename(filename);

	if (!filename) {
		logz.logerr(L_WARN, "filename is empty !");
		return (HTTP_STATUS_NOT_FOUND);
	}

	if (stat(filename, &s) < 0) {
		logz.logerr(L_WARN, "to execute stat on " + tmp_filename);
		return (HTTP_STATUS_NOT_FOUND);
	}

	if (s.st_mode & S_IFDIR) {
		logz.logerr(L_WARN, "'" + tmp_filename + "' is a directory/folder ! Populating directory list");
		_dir = new Directory(filename);
		return (HTTP_STATUS_OK);
	}

	_fd = ::open(filename, O_RDONLY, mode);

	if (_fd < 0) {
		logz.logerr(L_WARN, "opening " + tmp_filename + " failed due to error permissions !");
		return (HTTP_STATUS_FORBIDDEN);
	}
	logz.log(L_PASS, tmp_filename + " was opened successfully !");
	_filename = const_cast<char *>(filename);
	return (HTTP_STATUS_OK);
}
