/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:35:51 by stales            #+#    #+#             */
/*   Updated: 2023/03/03 17:26:30 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testunit.hpp"
#include "ipformat.hpp"
#include <iostream>
#include <cstdlib>

SUITE(ip_format_test)
{
	RUN_TEST(ip_format_test1);
}

int main(int argc, char **argv)
{
	GREATEST_MAIN_BEGIN();
	RUN_SUITE(ip_format_test);
	GREATEST_MAIN_END();
	return (0);
}
