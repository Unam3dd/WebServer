/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:32:27 by stales            #+#    #+#             */
/*   Updated: 2023/03/20 17:40:24 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include <cstdlib>

bool	check_overflow_port(const std::string &str)
{
	if (str.empty()) return (false);

	unsigned long long	_ov = std::atoll(str.c_str());
	unsigned short		_real = _ov;

	return (_ov != _real);
}
