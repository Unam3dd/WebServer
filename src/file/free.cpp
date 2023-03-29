/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:56:58 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/29 18:36:17 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.hpp"
#include <iostream> 

void	File::free(void)
{
	if (_data) {
		delete []_data;
		_data = NULL;
	}
	if (_dir)
	{
		delete _dir;
		_dir = NULL;
	}
}
