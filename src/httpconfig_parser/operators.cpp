/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:01:28 by stales            #+#    #+#             */
/*   Updated: 2023/03/05 16:02:10 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config_parser.hpp"

HttpConfigParser	&HttpConfigParser::operator=(const HttpConfigParser &h)
{
	if (this == &h) return (*this);
	return (*this);
}
