/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 01:41:25 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/21 08:56:32 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_utils.hpp"
#include "http_colors.hpp"
#include "webserver_help.hpp"
#include "webserver.hpp"
#include <iostream>

int main(int ac, char **av)
{
	help(ac, av);

	for (int i = ac - 1; i != 0; i--)
	{
		WebServer	ws(av[i]);

		if (DEBUG)
			std::cout << DBG << "[main] Calling ws.Parse()" << std::endl;
		ws.Parse();
	//	t_errcode err = ws.Parse();
	//	std::cout << DBG << ORANGE << av[i] << ": " << ws.GetErrorStrs().at(err) << std::endl;
	//	std::cout << ws << std::endl;
	}
	return (0);
}
