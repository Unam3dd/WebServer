/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 01:41:25 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/20 02:10:22 by ldournoi         ###   ########.fr       */
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
		case ERRPARSE_SPCORTAB:
			std::cout << "error space or tab misplaced" << std::endl;
			break;
		case ERRPARSE_DUP:
			std::cout << "error duplicate directive" << std::endl;
			break;
		case ERRPARSE_POST:
			std::cout << "error post" << std::endl;
			break;
		case ERRPARSE_TIMEOUT:
			std::cout << "error timeout" << std::endl;
			break;
		case ERRPARSE_COOKIES:
			std::cout << "error cookies" << std::endl;
			break;
		case ERRPARSE_UPLOADS:
			std::cout << "error uploads" << std::endl;
			break;
		case ERRPARSE_DIRLIST:
			std::cout << "error dirlist" << std::endl;
			break;
		case ERRPARSE_CGI:
			std::cout << "error cgi" << std::endl;
			break;
		case ERRPARSE_METHODS:
			std::cout << "error methods" << std::endl;
			break;
		case ERRPARSE_UPLOADDIR:
			std::cout << "error upload dir" << std::endl;
			break;
		default:
			std::cout << "Error" << std::endl;
			break;
	}

	std::cout << ws << std::endl;

	return (0);
}
