/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_colors.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 02:27:43 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/26 16:34:29 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef HTTP_COLORS_HPP
#define HTTP_COLORS_HPP

#define GREY	"\033[30m"
#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define ORANGE	"\033[33m"
#define BLUE	"\033[34m"
#define PURPLE	"\033[35m"
#define CYAN	"\033[36m"
#define WHITE	"\033[37m"
#define RESET	"\033[00m"
#define BGBLACK "\033[40m"
#define	BGREG	"\033[41m"
#define BGGREEN "\033[42m"
#define BGBROW	"\033[43m"
#define BGBLUE	"\033[44m"
#define BGPURPLE "\033[45m"
#define BGCYAN	 "\033[46m"
#define BGGREY	"\033[47m"
#define SUCCESS "[\033[32m SUCCESS \033[00m]"
#define DBG 	"[\033[36m DEBUG \033[00m]"
#define WARN	"[\033[33m WARNING \033[00m]"
#define FAIL	"[\033[31m FAIL \033[00m]"
#define TICK	"\n[\033[0;32m\xE2\x9C\x94\033[0m]"

#endif
