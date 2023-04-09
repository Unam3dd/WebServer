#include "http_response.hpp"

bool HttpResponse::_versionAllowed(){
	if (_request.getVersion() != "HTTP/1.0" && _request.getVersion() != "HTTP/1.1")
		return false;
	return true;
}

bool HttpResponse::_methodAllowed(){
	methods_t methods;
	this->_reqcfg ? methods = this->_reqcfg->GetMethods() : methods = this->_srvcfg->GetMethods();

	if (   (_request.getMethod() & GET 		&& !(methods & GET))
		|| (_request.getMethod() & POST		&& !(methods & POST))
		|| (_request.getMethod() & PUT		&& !(methods & PUT))
		|| (_request.getMethod() & DELETE	&& !(methods & DELETE))
		|| (_request.getMethod() & UNKNOWN))
		return false;
	return true;
}
