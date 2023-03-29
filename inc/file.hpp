/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:13:34 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/29 18:43:38 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "http_status.hpp"
#ifndef FILE_HPP
#define FILE_HPP

typedef unsigned long long file_size_t;

#include "directory.hpp"
#include <string>
#include <fcntl.h>

/*
 * @class File class
 */
class File
{
	// @brief Public Methods
	public:
		
		// @brief Default constructor
		File(void);
		
		/*
		 * @brief overloaded constructor
		 *
		 * @param filename: const char *	File to open and read
		 * @param flags:	int				(O_RDONLY | O_RDWR)
		 * @param mode:		unsigned int	S_IRUSR
		 */
		File(const char *filename, int flags, mode_t mode);
		
		// @brief Copy constructor
		File(const File& f);

		// @brief operator assignement
		File	&operator=(const File& f);

		// @brief Default destructor
		~File(void);

		/*
		 * @brief open file and reading methods
		 *
		 * @param filename: const char *	File to open
		 * @param flags:	int				O_RDONLY | O_RDWR
		 * @param mode:		unsigned int	S_IRUSR
		 *
		 * @return true if file was opened successfully otherwise is an error
		 */
		bool		open(const char *filename, int flags, mode_t mode);

		/*
		 * @brief open file and reading methods
		 *
		 * @param filename: const char *	File to open
		 * @param mode:		unsigned int	S_IRUSR
		 *
		 * @return HTTP_STATUS_OK if file or directory was opened successfully otherwise is an error
		 */
		http_status_code_t open(const char *filename, mode_t mode);

		// @brief Read Methods, read from fd and write it on heap memory area pointed by _data
		file_size_t	read(void);

		// @brief Free _data buffer
		void		free(void);

		// @brief close file fd
		void		close(void);

		// Accessors
		const char			*getFilename(void) const;
		const char			*getData(void) const;
		int					getFd(void) const;
		file_size_t			length(void) const;
		file_size_t			size(void) const;

	private:
		// @brief Directory object, used in case the path is a directory
		Directory	*_dir;

		// @brief pointer to heap zone memory, which represent file data
		char		*_data;

		// @brief name of file
		char		*_filename;

		// @brief Size of file
		file_size_t	_size;

		// @brief	fd of file
		int			_fd;
};

#endif
