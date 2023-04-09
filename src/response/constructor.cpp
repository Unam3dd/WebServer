#include "http_response.hpp"
#include "http_utils.hpp"
#include "http_colors.hpp"
#include "http_status.hpp"
#include <iostream>

/*
 * @brief: constructor for the HttpResponse class.
 * 
 * @param: req: the HttpRequest object for which to generate the response.
 *
 * @return: none. the response is generated and stored in the _fullresponse
 * attribute. it is gettable with the getResponse() method.
 *
 */
HttpResponse::HttpResponse(const HttpRequest &req) : _request(req)
{
	this->_srvcfg = _getSrvConfig(_request.getHeaders().at("host"), _request.getPort());
	this->_reqcfg = _getReqConfig(this->_srvcfg, _request.getUri());
	this->_reqcfg ? this->_status = static_cast<http_status_code_t>(this->_reqcfg->GetHttpResponseCode()) : this->_status = HTTP_STATUS_OK;
	this->_contenttype = "";

	
	if (!_versionAllowed()){
		_status = HTTP_STATUS_VERSION_NOT_SUPPORTED;
		this->_contenttype = "text/html";
		this->_body = this->_getErrorPageContent(this->_status);
		this->_generateResponse();
		if (DEBUG)
			std::cout << DBG << "[HttpResponse] HTTP version '" << _request.getVersion() << "' not supported" << std::endl;
		return ;
	}

	if (!_methodAllowed())
	{
		_status = HTTP_STATUS_METHOD_NOT_ALLOWED;
		this->_contenttype = "text/html";
		this->_body = this->_getErrorPageContent(this->_status);
		this->_generateResponse();
		if (DEBUG)
			std::cout << DBG << "[HttpResponse] Method '" << STR_METHOD(_request.getMethod()) << "' not allowed" << std::endl;
		return ;
	}

	if (_request.getMethod() & GET){
		this->_prepareGetResponse();
		if (this->_reqcfg && this->_reqcfg->GetHttpResponseCode() != HTTP_STATUS_OK)
			this->_status = static_cast<http_status_code_t>(this->_reqcfg->GetHttpResponseCode());
		this->_generateResponse();
	}

	/*
	if (_request.getMethod() & POST){
	   this->_preparePostResponse();
		if (this->_reqcfg && this->_reqcfg->GetHttpResponseCode() != HTTP_STATUS_OK)
			this->_status = static_cast<http_status_code_t>(this->_reqcfg->GetHttpResponseCode());
	   this->_generateResponse();
	   return ;
	}

	if (_request.getMethod() & PUT){
	   this->_preparePutResponse();
		if (this->_reqcfg && this->_reqcfg->GetHttpResponseCode() != HTTP_STATUS_OK)
			this->_status = static_cast<http_status_code_t>(this->_reqcfg->GetHttpResponseCode());
	   this->_generateResponse();
	   return ;
	}

	if (_request.getMethod() & DELETE){
	   this->_prepareDeleteResponse();
		if (this->_reqcfg && this->_reqcfg->GetHttpResponseCode() != HTTP_STATUS_OK)
			this->_status = static_cast<http_status_code_t>(this->_reqcfg->GetHttpResponseCode());
	   this->_generateResponse();
	   return ;
	}
	*/
	if (DEBUG)
	{
		std::cout << DBG << "[HttpResponse::HttpResponse()] Host: " << _request.getHeaders().at("host") << std::endl;
		std::cout << DBG << "[HttpResponse::HttpResponse()] Port: " << _request.getPort() << std::endl;
		std::cout << DBG << "[HttpResponse::HttpResponse()] Uri: " << _request.getUri() << std::endl;
		std::cout << DBG << "[HttpResponse::HttpResponse()] Server config chosen: "; PRINT_VECTOR_STR(this->_srvcfg->GetServerNames(), std::cout); std::cout << std::endl;
		std::cout << DBG << "[HttpResponse::HttpResponse()] Request config chosen: ";
		this->_reqcfg == NULL ? std::cout << "none" : std::cout << this->_reqcfg->GetScope(); std::cout << std::endl;
		std::cout << DBG << "[HttpResponse::HttpResponse()] Full response: "; this->_contenttype != "text/html" ? std::cout << BLUE << "Binary File." << RESET << std::endl : std::cout << std::endl << _fullresponse << std::endl;
	}
}
