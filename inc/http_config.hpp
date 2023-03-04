/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_config.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 01:54:26 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/04 02:18:16 by sam0verfl0w      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef HTTP_CONFIG_HPP
#define HTTP_CONFIG_HPP

#include <fstream>

/*********************************************************************
* @class    HttpConfig class
*********************************************************************/
class HttpConfig
{
	/*
	 * Public Methods
	 */
	public:
		/*@brief Default constructor */
		HttpConfig(void);
		/* @brief Overloaded constructor
		 * @param filename: const std::string&
		*/
		HttpConfig(const std::string& filename);
		/*
		 * @brief Copy constrcutor
		 * @param c: reference to a HttpConfig object
		 */
		HttpConfig(const HttpConfig& c);
		/*
		 *	@brief Operator assignment
		 */
		HttpConfig	&operator=(const HttpConfig& c);
		/*
		 * @brief Default Destructor
		 */
		~HttpConfig(void);

	/*
	 * Privates Attributes
	 */
	private:
		std::fstream	_f;
};

#endif
