/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:22:54 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/25 21:45:29 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.hpp"
#include <fcntl.h>

File::File(void): _data(NULL), _filename(NULL), _size(0), _fd(-1) {}

File::File(const char *filename, int flags, mode_t mode): _data(NULL), _filename(NULL), _size(0), _fd(-1)
{
	if (!this->open(filename, flags, mode))
		return ;
	this->read();
}

File::File(const File& f)
{
	if (this == &f) return ;
	*this = f;
}
