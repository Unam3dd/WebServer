/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:20:14 by stales            #+#    #+#             */
/*   Updated: 2023/03/29 15:35:51 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <sstream>
#include <string>

typedef unsigned int index_t;

bool	check_overflow_port(const std::string& str);

template <typename T>
std::string	NumberToString(T num) { std::ostringstream s; s << num; return (s.str()); }

#endif
