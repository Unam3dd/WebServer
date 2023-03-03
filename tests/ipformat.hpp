/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipformat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:24:50 by stales            #+#    #+#             */
/*   Updated: 2023/03/03 17:29:22 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//////////////////////////////////
//
//	       INCLUDES
//
/////////////////////////////////

#include "greatest/greatest.h"
#include "http_utils.hpp"
#include <string>
#include <stdint.h>

//////////////////////////////////
//
//	       FUNCTIONS
//
/////////////////////////////////

TEST	ip_format_test1(void)
{
	const std::string	addrs_ip[5] = {
		"127.0.0.1", "0.0.0.0", "255.255.255.255",
		"192.168.1.1", "172.17.0.1"
	};

	for (uint64_t i = 0; i < sizeof(addrs_ip)/sizeof(std::string); i++)
		ASSERT_EQ(check_format_ip(addrs_ip[i]), true);
	PASS();
}

