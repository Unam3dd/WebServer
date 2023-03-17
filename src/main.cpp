/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 01:41:25 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/17 15:31:07 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserver_help.hpp"
#include "webserver.hpp"
#include <iostream>

int main(int ac, char **av)
{
	help(ac, av);

	WebServer	ws(av[1]);

	switch(ws.Parse())
	{
		case ERRPARSE_OK:
			std::cout << "OK" << std::endl;
			break;
		case ERRPARSE_NEWSRVBLK:
			std::cout << "Error new server block" << std::endl;
			break;
		case ERRPARSE_NEWLOCBLK:
			std::cout << "error new location block" << std::endl;
			break;
		default:
			std::cout << "Error" << std::endl;
			break;
	}

	return (0);
}
