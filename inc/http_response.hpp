#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#include "http_request.hpp"
#include "http_request_config.hpp"
#include "http_config.hpp"
#include "http_status.hpp"
#include "utils.hpp"
#include <map>

class HttpResponse{
	public:
		HttpResponse(int status);
		HttpResponse(const HttpRequest &req);
		~HttpResponse(void);

		inline http_status_code_t	getStatusCode(void) const { return (_status); }
		inline const std::string	getStatusCodeStr(http_status_code_t	s) const { return (NumberToString(s)); }
		inline const std::string	getStatusCodeStr(void) const { return (NumberToString(_status)); }
		inline const std::string&	getVersion(void) const { return (_version); }
		inline const std::string&	getBody(void) const { return (_body); }
		inline const std::string&	getResponse(void) const { return _fullresponse; }
		size_t						writeResponse(const std::string& str);


	private:
		/*
		 * private members
		 */
		HttpRequest			_request;
		HttpServerConfig*	_srvcfg;
		HttpRequestConfig*	_reqcfg;
		std::vector<char*>	_cgiargv;
		std::vector<char*>	_cgienvp;
		http_status_code_t	_status;
		std::string			_contenttype;
		std::string			_version;
		std::string			_body;
		std::string			_fullresponse;
		std::string			_cgibuf;

		/*
		 * private methods
		 */
		HttpServerConfig*	_getSrvConfig(const std::string& host, port_t port);
		HttpRequestConfig*	_getReqConfig(const HttpServerConfig* cfg, const std::string& uri);
		std::string			_getErrorPageContent(http_status_code_t status);
		std::string			_getContentType(const std::string& uri);
		std::string			_getQuery(void);
		bool				_isDirectory(std::string& path);
		bool				_versionAllowed(void);
		bool				_methodAllowed(void);
		int					_processCgi(const std::string& path, const std::string& file);
		void				_generateResponse(void);
		void				_generateResponseCgi(void);
		void				_prepareResponse(void);
		void				_prepareDeleteResponse(void);
		void				_createCgiArgv(const std::string& path, const std::string& file);
		void				_createCgiEnvp(const std::string& file);
};

#endif
