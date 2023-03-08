/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 01:41:25 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/08 01:30:00 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_utils.hpp"
#include "http_server.hpp"
#include "http_config.hpp"
#include "http_config_parser.hpp"
#include <fcntl.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>

void	show_usage(const char *path)
{
	std::cerr << "usage: " << path << " [config] --help/-h" << std::endl;
	exit(1);
}

void	show_help(const char *path)
{
	std::cout << "usage: " << path << " [config] --help/-h" << std::endl;
	std::cout << "\t--generate \tGenerate default config file" << std::endl;
	std::cout << "\t--help     \tShow this page" << std::endl;
	std::cout << "\t--version  \tVersion of RocketServer" << std::endl;
	std::cout << std::endl;
	exit(0);
}

void	show_version(void)
{
	std::cout << "Version : " <<  VERSION << std::endl;
	exit(0);
}

void	help(int ac, char **av)
{
	if (ac != 2) show_usage(av[0]);

	if (av[1] && (!std::strcmp(av[1], "--help") || !std::strcmp(av[1], "-h")))
		show_help(av[0]);
	else if (av[1] && !std::strcmp(av[1], "--version"))
		show_version();
}

int main(int ac, char **av)
{
	help(ac, av);

	HttpConfig	config(av[1]);
	HttpServer	server("127.0.0.1", 8080);
	
	server.Listen(SOMAXCONN);

	return (0);
}
