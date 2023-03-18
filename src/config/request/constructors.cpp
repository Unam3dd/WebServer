/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:09:58 by stales            #+#    #+#             */
/*   Updated: 2023/03/18 21:54:43 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_request_config.hpp"

HttpRequestConfig::HttpRequestConfig(const std::string& scope): _scope(scope){
	_parseMap["index"] = &HttpRequestConfig::SetIndexes;
	_parseMap["errpage"] = &HttpRequestConfig::SetErrorPages;
	_parseMap["docroot"] = &HttpRequestConfig::SetRoot;
	_parseMap["session_path"] = &HttpRequestConfig::SetSessionPath;
	_parseMap["timeout"] = &HttpRequestConfig::SetServerTimeout;
	_parseMap["max_post_size"] = &HttpRequestConfig::SetMaxPostSize;
	_parseMap["cookies"] = &HttpRequestConfig::SetCookies;
	_parseMap["uploads"] = &HttpRequestConfig::SetUploads;
	_parseMap["upload_dir"] = &HttpRequestConfig::SetUploadDir;
	_parseMap["dirlist"] = &HttpRequestConfig::SetDirList;
	_parseMap["cgi"] = &HttpRequestConfig::SetCgi;
	_parseMap["methods"] = &HttpRequestConfig::SetMethods;
	_parseMap["redirect"] = &HttpRequestConfig::SetRedirect;
	_parseMap["http_response_code"] = &HttpRequestConfig::SetHttpResponseCode;
}

HttpRequestConfig::HttpRequestConfig(const HttpRequestConfig& c){
	*this = c;
}
