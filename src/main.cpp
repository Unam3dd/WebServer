/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 01:41:25 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/09 17:34:14 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_utils.hpp"
#include "http_server.hpp"
#include "http_config.hpp"
#include "http_config_parser.hpp"
#include "webserver_help.hpp"

int main(int ac, char **av)
{
	help(ac, av);

	HttpConfig	config(av[1]);
	HttpConfigParser	cparser;

	cparser.Parse(config);

	return (0);
}
