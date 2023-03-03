/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipformat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:24:50 by stales            #+#    #+#             */
/*   Updated: 2023/03/03 19:37:48 by stales           ###   ########.fr       */
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
		"127.0.0.2", "0.0.0.0", "255.255.255.255",
		"192.168.1.1", "172.17.0.255"
	};

	ASSERT_EQ(check_format_ip(addrs_ip[0]), true);
	ASSERT_EQ(check_format_ip(addrs_ip[1]), true);
	ASSERT_EQ(check_format_ip(addrs_ip[2]), true);
	ASSERT_EQ(check_format_ip(addrs_ip[3]), true);
	PASS();
}

TEST	ip_format_test2(void)
{
	const std::string	addrs_ip[5] = {
		"pommedeterre", "1278.45.0.14",
		"....", "", "127.0.0.256"
	};
	
	ASSERT_EQ(check_format_ip(addrs_ip[0]), false);
	ASSERT_EQ(check_format_ip(addrs_ip[1]), false);
	ASSERT_EQ(check_format_ip(addrs_ip[2]), false);
	ASSERT_EQ(check_format_ip(addrs_ip[3]), false);
	ASSERT_EQ(check_format_ip(addrs_ip[4]), false);
	PASS();
}

TEST	ip_format_test3(void)
{
	const std::string	addrs_ip[5] = {
		"0...", "192A.168.1.1",
		"1.1.1.1.1", ".1.1.1.1.", "1A.1.1.1"
	};

	ASSERT_EQ(check_format_ip(addrs_ip[0]), false);
	ASSERT_EQ(check_format_ip(addrs_ip[1]), false);
	ASSERT_EQ(check_format_ip(addrs_ip[2]), false);
	ASSERT_EQ(check_format_ip(addrs_ip[3]), false);
	ASSERT_EQ(check_format_ip(addrs_ip[4]), false);
	PASS();
}
