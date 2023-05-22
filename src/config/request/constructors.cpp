/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:09:58 by stales            #+#    #+#             */
/*   Updated: 2023/05/22 23:17:17 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_request_config.hpp"

HttpRequestConfig::HttpRequestConfig(const std::string& scope): _scope(scope){
	_parseMap["index"] = &HttpRequestConfig::SetIndexes;
	_parseMap["errpage"] = &HttpRequestConfig::SetErrorPages;
	_parseMap["docroot"] = &HttpRequestConfig::SetRoot;
	_parseMap["max_post_size"] = &HttpRequestConfig::SetMaxPostSize;
	_parseMap["cookies"] = &HttpRequestConfig::SetCookies;
	_parseMap["uploads"] = &HttpRequestConfig::SetUploads;
	_parseMap["dirlist"] = &HttpRequestConfig::SetDirList;
	_parseMap["cgi"] = &HttpRequestConfig::SetCgi;
	_parseMap["methods"] = &HttpRequestConfig::SetMethods;
	_parseMap["http_response_code"] = &HttpRequestConfig::SetHttpResponseCode;

	_root = "/var/www/html";
	_methods = static_cast<methods_t>(GET | POST | PUT | DELETE);
	_max_size_post = 1000000;
	_cookies = true;
	_uploads = true;
	_dirlist = true;
	_response_code = 200;
	_errpages[E400].code = 400;
	_errpages[E400].path = "default";
	_errpages[E401].code = 401;
	_errpages[E401].path = "default";
	_errpages[E403].code = 403;
	_errpages[E403].path = "default";
	_errpages[E404].code = 404;
	_errpages[E404].path = "default";
	_errpages[E405].code = 405;
	_errpages[E405].path = "default";
	_errpages[E408].code = 408;
	_errpages[E408].path = "default";
	_errpages[E500].code = 500;
	_errpages[E500].path = "default";
	_errpages[E501].code = 501;
	_errpages[E501].path = "default";
	_errpages[E502].code = 502;
	_errpages[E502].path = "default";
	_errpages[E505].code = 505;
	_errpages[E505].path = "default";
}

HttpRequestConfig::HttpRequestConfig(const HttpRequestConfig& c){
	*this = c;
}
