/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:20:14 by stales            #+#    #+#             */
/*   Updated: 2023/05/24 19:41:15 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <sstream>
#include <string>

typedef unsigned int index_t;
typedef struct mime_content_type_t mime_content_type_t;

struct mime_content_type_t
{
	const char	*ext[2];
	const char	*str;
	size_t		ext_len;
};

bool	check_overflow_port(const std::string& str);

template <typename T>
std::string	NumberToString(T num) { std::ostringstream s; s << num; return (s.str()); }

template <typename T>
T			StringToNumber(const std::string& str) { std::istringstream ss(str); T num; ss >> num; return (num); }
#endif
