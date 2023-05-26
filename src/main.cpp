/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 01:41:25 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/04/19 17:05:24 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_utils.hpp"
#include "webserver_help.hpp"
#include "webserver.hpp"
#include <iostream>

int main(int ac, char **av, char **envp)
{
	SG_ENVP(envp);

	help(ac, av);

	WebServer	ws(av[1] ? av[1] : DEFAULT_CONF);
	SG_WebServer(&ws);

	if (ws.Parse()) {
		std::cout << "Error during parsing configuration file !" << std::endl;
		return (1);
	}
	ws.Run();
	return (0);
}
