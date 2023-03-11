/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 01:41:25 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/10 18:05:18 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_utils.hpp"
#include "http_server.hpp"
#include "http_config.hpp"
#include "http_colors.hpp"
#include "http_config_parser.hpp"
#include "webserver_help.hpp"
#include <iostream>

int main(int ac, char **av)
{
	help(ac, av);

	HttpConfig	config(av[1]);
	HttpConfigParser	cparser;




	return (0);
}
