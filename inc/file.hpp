/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:13:34 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/04 18:56:45 by sam0verfl0w      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef FILE_HPP
#define FILE_HPP

typedef unsigned long long file_size_t;

#include <string>
#include <fcntl.h>

class File
{
	public:
		File(void);
		File(const char *filename, int flags, mode_t mode);
		File(const File& f);
		File	&operator=(const File& f);
		~File(void);

		bool		open(const char *filename, int flags, mode_t mode);
		file_size_t	read(void);
		void		free(void);
		void		close(void);

		const char			*getFilename(void) const;
		const char			*getData(void) const;
		int					getFd(void) const;
		file_size_t			length(void) const;
		file_size_t			size(void) const;

	private:
		char		*_data;
		char		*_filename;
		file_size_t	_size;
		int			_fd;
};

#endif
