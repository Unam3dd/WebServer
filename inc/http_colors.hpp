/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_colors.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 02:27:43 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/04/26 20:38:42 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef HTTP_COLORS_HPP
#define HTTP_COLORS_HPP

#define ESC				"\x1b"

#define GREY			ESC "[30m"
#define RED				ESC "[31m"
#define GREEN			ESC "[32m"
#define ORANGE			ESC "[33m"
#define BLUE			ESC "[34m"
#define PURPLE			ESC "[35m"
#define CYAN			ESC "[36m"
#define WHITE			ESC "[37m"
#define RESET			ESC "[00m"
#define BGBLACK 		ESC "[40m"
#define	BGREG			ESC "[41m"
#define BGGREEN 		ESC "[42m"
#define BGBROW			ESC "[43m"
#define BGBLUE			ESC "[44m"
#define BGPURPLE		ESC "[45m"
#define BGCYAN			ESC "[46m"
#define BGGREY			ESC "[47m"
#define GOTO_COL		ESC "[13G"
#define SUCCESS 		"[" GREEN	" SUCCESS "		RESET "]" GOTO_COL
#define DBG 			"[" CYAN	" DEBUG "		RESET "]" GOTO_COL
#define WARN			"[" ORANGE	" WARNING "		RESET "]" GOTO_COL
#define INFO			"[" CYAN	" INFO "		RESET "]" GOTO_COL
#define FAIL			"[" RED		" FAIL "		RESET "]" GOTO_COL
#define TICK			"\n[" GREEN	"\xE2\x9C\x94"	RESET "]"

#endif
