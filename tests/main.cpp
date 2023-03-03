/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:35:51 by stales            #+#    #+#             */
/*   Updated: 2023/03/03 16:26:25 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testunit.hpp"
#include <iostream>
#include <cstdlib>

void	show_usage(const char *str)
{
	std::cerr << "usage: " << str << " --help" << std::endl;
	exit(1);
}

SUITE(ip_format_test)
{
	RUN_TEST(ip_format_test1);
}

int main(int argc, char **argv)
{
	if (argc < 2)
		show_usage(argv[0]);
	GREATEST_MAIN_BEGIN();
	RUN_SUITE(ip_format_test);
	GREATEST_MAIN_END();
	return (0);
}
