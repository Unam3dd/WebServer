/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testunit.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:19:31 by stales            #+#    #+#             */
/*   Updated: 2023/03/03 15:24:32 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef TESTUNIT_HPP
#define TESTUNIT_HPP

#include "greatest/greatest.h"

GREATEST_MAIN_DEFS();

/*
 * @brief	IP Format Test 
 *
 * @file	ipformat.cpp
*/

TEST	ip_format_test1(void);
TEST	ip_format_test2(void);
TEST	ip_format_test3(void);
TEST	ip_format_test4(void);

SUITE(ip_format_test)
{
	RUN_TEST(ip_format_test1);
	RUN_TEST(ip_format_test2);
	RUN_TEST(ip_format_test3);
	RUN_TEST(ip_format_test4);
}

#endif
