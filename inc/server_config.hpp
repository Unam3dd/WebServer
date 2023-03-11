/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_config.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:47:57 by stales            #+#    #+#             */
/*   Updated: 2023/03/11 14:02:03 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CONFIG_HPP
#define SERVER_CONFIG_HPP

#include <string>
#include <vector>
#include "request_config.hpp"
#include "file.hpp"

class ServerConfig: public File
{
	public:
		ServerConfig(void);
		ServerConfig(const std::string& filename);
		~ServerConfig(void);

		bool	Parse(void);
	
	private:
		std::vector<RequestConfig> _rconfig;
};

#endif
