/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_config.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam0verfl0w <stales@student.42angouleme.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 01:54:26 by sam0verfl0w       #+#    #+#             */
/*   Updated: 2023/03/04 19:03:53 by sam0verfl0w      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef HTTP_CONFIG_HPP
#define HTTP_CONFIG_HPP

#include "file.hpp"
#include <sys/stat.h>

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

		//		Read file method
		size_t	read(void);

		//		Open file method
		bool	open(const std::string& filename);

		//		Close file method
		void	close(void);

		// Accessors
		const std::string&	getFilename(void) const;

	/*
	 * Privates Attributes
	 */
	private:
		std::string				_fname;
		File					_f;
};

#endif
