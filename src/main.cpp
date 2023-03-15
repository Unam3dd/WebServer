/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 01:41:25 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/15 12:41:52 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserver_help.hpp"
#include "webserver.hpp"
#include <iostream>

int main(int ac, char **av)
{
	help(ac, av);

	WebServer	ws(av[1]);

	ws.Parse();

	return (0);
}
