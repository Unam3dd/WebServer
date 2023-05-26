/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserver_help.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:06:52 by stales            #+#    #+#             */
/*   Updated: 2023/03/09 17:08:37 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef WEBSERVER_HELP_HPP
#define WEBSERVER_HELP_HPP

// void	show_usage(const char *path);
void	show_help(const char *path);
void	show_version(void);
void	help(int ac, char **av);

#endif
