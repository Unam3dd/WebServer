/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testunit.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:19:31 by stales            #+#    #+#             */
/*   Updated: 2023/03/03 16:26:09 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef TESTUNIT_HPP
#define TESTUNIT_HPP

#include "greatest/greatest.h"
#include "http_utils.hpp"
#include <string>
#include <stdint.h>

GREATEST_MAIN_DEFS();

/*
 * @brief	IP Format Test 
 *
 * @file	ipformat.cpp
*/

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
		ASSERT_EQ(IS_BAD_IP(addrs_ip[i]), 1);
	PASS();
}


#endif
