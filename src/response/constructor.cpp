#include "http_response.hpp"
#include "http_utils.hpp"
#include "logger.hpp"
#include "http_status.hpp"
#include "http_request.hpp"
#include <cstring>
#include <iostream>

bool	isReqTraversal(std::string root, std::string uri)
{
	char	*real_path_root;
	char	*real_path_uri;
	bool	is_traversal;

	real_path_root = realpath(root.c_str(), NULL);
	uri = root + "/" + uri;
	real_path_uri = realpath(uri.c_str(), NULL);
	if (!real_path_uri || !strncmp(real_path_root, real_path_uri, strlen(real_path_root)))
		is_traversal = false;
	else
		is_traversal = true;
	if (real_path_root)
		free(real_path_root);
	if (real_path_uri)
		free(real_path_uri);
	return (is_traversal);
}

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

	if (this->_request.isBadRequest() || !_request.getHeaders().at("host").length())
	{
		this->_status = HTTP_STATUS_BAD_REQUEST;
		this->_contenttype = "text/html";
		this->_body = this->_getErrorPageContent(this->_status);
		this->_generateResponse();
		logz.log(L_DEBUG, "Bad request");
		return ;
	}

	if (isReqTraversal(this->_srvcfg->GetRoot(), req.getUri()))
	{
		this->_status = HTTP_STATUS_NOT_FOUND;
		this->_contenttype = "text/html";
		this->_body = this->_getErrorPageContent(this->_status);
		this->_generateResponse();
		logz.log(L_WARN | L_BYPASS, "Uri " + req.getUri() + " is traversal. blocking it");
		return ;
	}

	if (!_versionAllowed()){
		this->_status = HTTP_STATUS_VERSION_NOT_SUPPORTED;
		this->_contenttype = "text/html";
		this->_body = this->_getErrorPageContent(this->_status);
		this->_generateResponse();
		logz.log(L_WARN, "HTTP version '" + _request.getVersion() + "' not supported");
		return ;
	}

	if (!_methodAllowed())
	{
		this->_status = HTTP_STATUS_METHOD_NOT_ALLOWED;
		this->_contenttype = "text/html";
		this->_body = this->_getErrorPageContent(this->_status);
		this->_generateResponse();
		logz.log(L_WARN, "HTTP method '" + logz.get_methods(_request.getMethod()) + "' not allowed");
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
		logz.log(L_WARN, "POST body too large");
		return ;
	}

	this->_prepareResponse();
	if (strlen(this->_cgibuf.data()) > 0)
		return ;
	if (this->_reqcfg && this->_reqcfg->GetHttpResponseCode() != HTTP_STATUS_OK)
		this->_status = SANITIZE_AND_CAST_INT_TO_HTTP_STATUS(this->_reqcfg->GetHttpResponseCode());
	this->_generateResponse();

	logz.log(L_DEBUG, "Host: " + _request.getHeaders().at("host"));
	logz.log(L_DEBUG, "Port: " + logz.itoa(_request.getPort()));
	logz.log(L_DEBUG, "Uri: " + _request.getUri());
	std::string tmp;
	FOREACH_VECTOR(std::string, this->_srvcfg->GetServerNames(), it)
		tmp += *it;
	logz.log(L_DEBUG, "Server config chosen: " + tmp);
	logz.log(L_DEBUG, "Request config choosen: " + (this->_reqcfg == NULL ? "None" : this->_reqcfg->GetScope()));
	logz.log(L_DEBUG, "Full response: " + (this->_contenttype != "text/html" ? ANSI_FMT(B, "Binary File.") : "\n" + this->_fullresponse));
	logz.log(L_DEBUG, (this->_cgibuf.data() ? "CGI Buffer content: \n" + _cgibuf : "No CGI."));
}

HttpResponse::HttpResponse(int status) : _request(HttpRequest()), _srvcfg(NULL), _reqcfg(NULL){
	// TOCHECK : CREATE A LOT OF OUTPUT
	// logz.log(L_DEBUG, "Creating forced error response (via constructor surcharge)");
	this->_status = SANITIZE_AND_CAST_INT_TO_HTTP_STATUS(status);
	this->_contenttype = "text/html";
	this->_body = this->_getErrorPageContent(this->_status);
	this->_generateResponse();
}
