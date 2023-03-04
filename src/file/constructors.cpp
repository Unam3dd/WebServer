/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:22:54 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/04 15:26:03 by sam0verfl0w      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.hpp"

File::File(void): _data(NULL), _filename(NULL), _size(0), _fd(-1) {}

File::File(const char *filename): _data(NULL), _filename(NULL), _size(0), _fd(-1)
{
	(void)filename;
}

File::File(const File& f)
{
	if (this == &f) return ;
	*this = f;
}
