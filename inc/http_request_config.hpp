/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_request_config.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:17:45 by stales            #+#    #+#             */
/*   Updated: 2023/03/13 17:22:03 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST_CONFIG_HPP
#define HTTP_REQUEST_CONFIG_HPP

#include "http_config.hpp"

class HttpRequestConfig: protected HttpServerConfig
{
	public:
		HttpRequestConfig(void);
		HttpRequestConfig(const HttpRequestConfig& c);
		~HttpRequestConfig(void);
};

#endif
