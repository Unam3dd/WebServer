/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:12:16 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/04 19:19:28 by sam0verfl0w      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config.hpp"
#include <fcntl.h>
#include <sys/stat.h>

HttpConfig::HttpConfig(void): File() {}

HttpConfig::HttpConfig(const std::string& filename): File(filename.c_str(), O_RDONLY, S_IRUSR) {}

HttpConfig::HttpConfig(const HttpConfig& h): File(h) {};
