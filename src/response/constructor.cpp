#include "http_response.hpp"
#include "http_utils.hpp"
#include "http_colors.hpp"
#include "http_status.hpp"
#include "http_request.hpp"
#include <cstring>
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
	this->_reqcfg ? this->_status = SANITIZE_AND_CAST_INT_TO_HTTP_STATUS(this->_reqcfg->GetHttpResponseCode()) : this->_status = HTTP_STATUS_OK;
	this->_contenttype = "";
	
	if (this->_request.isBadRequest())
	{
		this->_status = HTTP_STATUS_BAD_REQUEST;
		this->_contenttype = "text/html";
		this->_body = this->_getErrorPageContent(this->_status);
		this->_generateResponse();
		if (DEBUG)
			std::cout << DBG << "[HttpResponse] Bad request" << std::endl;
		return ;
	}
	
	if (!_versionAllowed()){
		this->_status = HTTP_STATUS_VERSION_NOT_SUPPORTED;
		this->_contenttype = "text/html";
		this->_body = this->_getErrorPageContent(this->_status);
		this->_generateResponse();
		if (DEBUG)
			std::cout << DBG << "[HttpResponse] HTTP version '" << _request.getVersion() << "' not supported" << std::endl;
		return ;
	}

	if (!_methodAllowed())
	{
		this->_status = HTTP_STATUS_METHOD_NOT_ALLOWED;
		this->_contenttype = "text/html";
		this->_body = this->_getErrorPageContent(this->_status);
		this->_generateResponse();
		if (DEBUG)
			std::cout << DBG << "[HttpResponse] HTTP method '" << _request.getMethod() << "' not allowed" << std::endl;
		return ;
	}
	
	maxpost_size_t maxpost;
	if (this->_reqcfg && this->_reqcfg->GetMaxPostSize())
		maxpost = this->_reqcfg->GetMaxPostSize();
	else
		maxpost = this->_srvcfg->GetMaxPostSize();
	if (this->_request.getBody().size() > maxpost)
	{
		this->_status = HTTP_STATUS_PAYLOAD_TOO_LARGE;
		this->_contenttype = "text/html";
		this->_body = this->_getErrorPageContent(this->_status);
		this->_generateResponse();
		if (DEBUG)
			std::cout << DBG << "[HttpResponse] POST body too large" << std::endl;
		return ;
	}

	this->_prepareResponse();
	if (strlen(this->_cgibuf.data()) > 0)
		return ;
	if (this->_reqcfg && this->_reqcfg->GetHttpResponseCode() != HTTP_STATUS_OK)
		this->_status = SANITIZE_AND_CAST_INT_TO_HTTP_STATUS(this->_reqcfg->GetHttpResponseCode());
	this->_generateResponse();

	if (DEBUG)
	{
		std::cout << DBG << "[HttpResponse::HttpResponse()] Host: " << _request.getHeaders().at("host") << std::endl;
		std::cout << DBG << "[HttpResponse::HttpResponse()] Port: " << _request.getPort() << std::endl;
		std::cout << DBG << "[HttpResponse::HttpResponse()] Uri: " << _request.getUri() << std::endl;
		std::cout << DBG << "[HttpResponse::HttpResponse()] Server config chosen: "; PRINT_VECTOR_STR(this->_srvcfg->GetServerNames(), std::cout); std::cout << std::endl;
		std::cout << DBG << "[HttpResponse::HttpResponse()] Request config chosen: ";
		this->_reqcfg == NULL ? std::cout << "none" : std::cout << this->_reqcfg->GetScope(); std::cout << std::endl;
		std::cout << DBG << "[HttpResponse::HttpResponse()] Full response: "; this->_contenttype != "text/html" ? std::cout << BLUE << "Binary File." << RESET << std::endl : std::cout << std::endl << _fullresponse << std::endl;
		this->_cgibuf.data() ? std::cout << DBG << "[HttpResponse::HttpResponse()] CGI Buffer content: \n" << _cgibuf.data() << std::endl : std::cout << DBG << "[HttpResponse::HttpResponse()] No CGI." << std::endl;
	}
}

HttpResponse::HttpResponse(int status) : _request(HttpRequest()), _srvcfg(NULL), _reqcfg(NULL){
	if (DEBUG)
		std::cout << DBG << "[HttpResponse] Creating forced error response (via constructor surcharge)" << std::endl;
	this->_status = SANITIZE_AND_CAST_INT_TO_HTTP_STATUS(status);
	this->_contenttype = "text/html";
	this->_body = this->_getErrorPageContent(this->_status);
	this->_generateResponse();
}
