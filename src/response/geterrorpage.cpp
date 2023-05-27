/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geterrorpage.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:58:55 by ldournoi          #+#    #+#             */
/*   Updated: 2023/05/24 17:36:48 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logger.hpp"
#include "http_response.hpp"
#include "http_status.hpp"
#include "file.hpp"
#include <sys/stat.h>
#include <iostream>

/*
 * @brief: get the content of the error page for the given http status code.
 * if the error page specified by the config file is not found, return the
 * default error page.
 *
 * @param: httpstatus: the http status code for which to get the error page
 * content.
 *
 * @return: the content of the error page for the given http status code.
 * if the error page specified by the config file is not found, return the
 * default error page.
 *
 */
std::string	HttpResponse::_getErrorPageContent(http_status_code_t httpstatus){
	std::string	root;
	std::string path;
	std::string fullpath;
	errpagecode_t status;

	if (httpstatus == HTTP_STATUS_BAD_REQUEST)
		status = E400;
	else if (httpstatus == HTTP_STATUS_UNAUTHORIZED)
		status = E401;
	else if (httpstatus == HTTP_STATUS_FORBIDDEN)
		status = E403;
	else if (httpstatus == HTTP_STATUS_NOT_FOUND)
		status = E404;
	else if (httpstatus == HTTP_STATUS_METHOD_NOT_ALLOWED)
		status = E405;
	else if (httpstatus == HTTP_STATUS_REQUEST_TIMEOUT)
		status = E408;
	else if (httpstatus == HTTP_STATUS_LENGTH_REQUIRED)
		status = E411;
	else if (httpstatus == HTTP_STATUS_PAYLOAD_TOO_LARGE)
		status = E413;
	else if (httpstatus == HTTP_STATUS_INTERNAL_SERVER_ERROR)
		status = E500;
	else if (httpstatus == HTTP_STATUS_NOT_IMPLEMENTED)
		status = E501;
	else if (httpstatus == HTTP_STATUS_BAD_GATEWAY)
		status = E502;
	else if (httpstatus == HTTP_STATUS_VERSION_NOT_SUPPORTED)
		status = E505;
	else
		status = E500;

	if (!this->_srvcfg)
		return (SG_DefaultErrorPages(status));

	if (this->_reqcfg && this->_reqcfg->GetErrorPages()[status].path == "default" && this->_srvcfg->GetErrorPages()[status].path == "default")
		return (SG_DefaultErrorPages(status));
	else if (!this->_reqcfg && this->_srvcfg->GetErrorPages()[status].path == "default")
		return (SG_DefaultErrorPages(status));
	else if (this->_reqcfg && this->_reqcfg->GetErrorPages()[status].path != "default")
	{
		if (this->_reqcfg->GetRoot() == "")
			root = this->_srvcfg->GetRoot();
		else
			root = this->_reqcfg->GetRoot();
		path = this->_reqcfg->GetErrorPages()[status].path;
	}
	else if (this->_srvcfg->GetErrorPages()[status].path != "default")
	{
		root = this->_srvcfg->GetRoot();
		path = this->_srvcfg->GetErrorPages()[status].path;
	}
	fullpath = root + path;
	if (!FILE_EXISTS(fullpath.c_str())){
		logz.log(L_WARN, "Error page '" + fullpath + "' not found. Returning default error page.");
		return (SG_DefaultErrorPages(status));
	}
	struct stat st;
	stat(fullpath.c_str(), &st);
	if (st.st_mode & S_IRUSR)
	{
		File content(fullpath.c_str(), O_RDONLY, S_IRUSR);
		return (content.getData());
	}
	else{
		return (SG_DefaultErrorPages(status));
	}
	return ("");
}


