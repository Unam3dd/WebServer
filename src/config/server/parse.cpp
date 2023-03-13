/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:52:14 by stales            #+#    #+#             */
/*   Updated: 2023/03/13 19:00:15 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config.hpp"
#include <iostream>

int	HttpServerConfig::Parse(void)
{
	std::cout << this->getData() << std::endl;
	return (0);
}

int	HttpServerConfig::Parse(const std::string &path)
{
	if (path.empty()) return (1);

	std::cout << this->getData() << std::endl;

	return (0);
}
