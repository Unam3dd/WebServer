/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:08:48 by stales            #+#    #+#             */
/*   Updated: 2023/03/09 17:11:40 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserver_help.hpp"
#include "http_server.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>

/*********************************************************************
*
* @brief    show_usage		Show usage of this program
*
* @param    path:	const char * which is argv[0] 
*
*********************************************************************/

void	show_usage(const char *path)
{
	std::cerr << "usage: " << path << " [config] --help/-h" << std::endl;
	exit(1);
}

/*********************************************************************
*
* @brief    show_help		Show help of this program
*
* @param    path:	const char * which is argv[0] 
*
*********************************************************************/

void	show_help(const char *path)
{
	std::cout << "usage: " << path << " [config] --help/-h" << std::endl;
	std::cout << "\t--generate \tGenerate default config file" << std::endl;
	std::cout << "\t--help     \tShow this page" << std::endl;
	std::cout << "\t--version  \tVersion of RocketServer" << std::endl;
	std::cout << std::endl;
	exit(0);
}

/*********************************************************************
*
* @brief    show_version	Show version of this program
*
*********************************************************************/

void	show_version(void)
{
	std::cout << "Version : " <<  VERSION << std::endl;
	exit(0);
}

/*********************************************************************
*
* @brief    show_usage		Show usage of this program
*
* @param    path:	const char * which is argv[0] 
*
*********************************************************************/

void	help(int ac, char **av)
{
	if (ac != 2) show_usage(av[0]);

	if (av[1] && (!std::strcmp(av[1], "--help") || !std::strcmp(av[1], "-h")))
		show_help(av[0]);
	else if (av[1] && !std::strcmp(av[1], "--version"))
		show_version();
}
