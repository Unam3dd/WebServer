/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accessors.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:27:28 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/04 15:29:12 by sam0verfl0w      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.hpp"

const char	*File::getFilename(void) const { return (this->_filename); }

const char	*File::getData(void) const { return (this->_data); }

file_size_t	File::length(void) const { return (this->_size); }

file_size_t File::size(void) const { return (this->_size); }

int			File::getFd(void) const { return (this->_fd); }
