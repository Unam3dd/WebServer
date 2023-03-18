/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 01:41:25 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/18 16:04:42 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_utils.hpp"
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
		case ERRPARSE_UNKNOWN:
			std::cout << "error unknown config arg" << std::endl;
			break;
		case ERRPARSE_NEWSRVBLK:
			std::cout << "Error new server block" << std::endl;
			break;
		case ERRPARSE_NEWLOCBLK:
			std::cout << "error new location block" << std::endl;
			break;
		case ERRPARSE_ENDBLK:
			std::cout << "error end block" << std::endl;
			break;
		case ERRPARSE_SINGLEARG:
			std::cout << "error single argument" << std::endl;
			break;
		case ERRPARSE_NOARG:
			std::cout << "error no argument" << std::endl;
			break;
		case ERRPARSE_PORT:
			std::cout << "error port" << std::endl;
			break;
		case ERRPARSE_ERRPAGE:
			std::cout << "error error page" << std::endl;
			break;
		default:
			std::cout << "Error" << std::endl;
			break;
	}

	return (0);
}
