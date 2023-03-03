/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_formats.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:33:12 by stales            #+#    #+#             */
/*   Updated: 2023/03/03 19:44:29 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_utils.hpp"

#include <iostream>
#include <cstring>
#include <cstdlib>

bool	check_format_ip(const std::string& ip)
{
	char	*ptr = NULL;
	size_t	len = 0;

	// Check len because minimal is "0.0.0.0" and max "255.255.255.255"
	if (ip.empty() || (ip.size() < 0x7 || ip.size() > 0xF)) return (false);
	
	// false if string contains other char than "0123456789."
	if (std::strspn(ip.c_str(), "0123456789.") != ip.size())
		return (false);

	// You can use iterator but i prefer char *
	ptr = (char *)ip.c_str();

	for (int i = 0; *ptr && i < 4; i++) {
		len = std::strspn(ptr, "0123456789");
		
		// if len is 0 or greater than 3 is false
		if (!len || len > 3) return (false);

		// byte must be between 0 and 255
		if (std::atoi(ptr) > 0xFF) return (false);

		ptr += len;

		// count dot string contains more than . consecutively then its error 
		if (i < 3 && ptr && (std::strspn(ptr, ".") > 1 || *ptr != '.')) return (false);

		// if it's non last bytes increment for the next byte
		if (i < 3) ptr++;
	}
	return ((*ptr) ? false : true);
}
