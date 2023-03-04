/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:35:51 by stales            #+#    #+#             */
/*   Updated: 2023/03/04 01:19:23 by sam0verfl0w      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testunit.hpp"
#include "ipformat.hpp"
#include <iostream>
#include <cstdlib>

SUITE(ip_format_test)
{
	RUN_TEST(ip_format_test1);
	RUN_TEST(ip_format_test2);
	RUN_TEST(ip_format_test3);
	RUN_TEST(ip_format_test4);
}

int main(int argc, char **argv)
{
	GREATEST_MAIN_BEGIN();
	RUN_SUITE(ip_format_test);
	GREATEST_MAIN_END();
	return (0);
}
