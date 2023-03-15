/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:35:50 by stales            #+#    #+#             */
/*   Updated: 2023/03/15 19:22:37 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserver.hpp"
#include <iostream>

int	WebServer::Parse(const std::string& path)
{
	if (path.empty()) return (1);
	std::cout << this->getData() << std::endl;
	return (0);
}

int	WebServer::Parse(void)
{
	std::cout << this->getData() << std::endl;
	return (0);
}
