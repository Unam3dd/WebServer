#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#include "http_request.hpp"
#include "http_request_config.hpp"
#include "http_config.hpp"

class HttpResponse{
	public:
		HttpResponse(const HttpRequest &req);
		~HttpResponse(void);

		inline const std::string&	getResponse(void) const { return _fullresponse; }

	private:
		/*
		 * private members
		 */
		HttpRequest			_request;
		HttpServerConfig*	_srvcfg;
		HttpRequestConfig*	_reqcfg;
		std::string			_body;
		std::string			_fullresponse;
		int					_status;

		/*
		 * private methods
		 */
		HttpServerConfig*	_getSrvConfig(const std::string& host, port_t port);
		HttpRequestConfig*	_getReqConfig(const HttpServerConfig* cfg, const std::string& uri);
};

#endif
