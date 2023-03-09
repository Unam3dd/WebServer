/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:18:42 by stales            #+#    #+#             */
/*   Updated: 2023/03/09 19:21:57 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config_parser.hpp"
#include "http_colors.hpp"
#include <iostream>

void	HttpConfigParser::PrintConfigurationStatus(parse_config_status_t s)
{
	(s & 1) ?
		std::cout << FAIL << " Failed to parse configuration file !" << std::endl
		:
		std::cout << SUCCESS << " Configuration file parsed with success !" << std::endl;
}
