#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <map>
#include "http_utils.hpp"

class HttpRequest
{
	public:
		typedef t_status (HttpRequest::*t_parseMap)(const std::string &line);
		HttpRequest(void);
		HttpRequest(const std::string& req);
		~HttpRequest(void);

		void setMethod(const std::string& method);
		void setUri(const std::string& uri);
		void setVersion(const std::string& version);
		void setBody(const std::string& body);

		inline const std::map<std::string, std::string>& getHeaders(void) const { return _header; }
		inline const std::string& getUri(void) const { return _uri; }
		inline const std::string& getVersion(void) const { return _version; }
		inline const std::string& getBody(void) const { return _body; }
		inline const methods_t&   getMethod(void) const { return _method; }

		friend std::ostream& operator<<(std::ostream& os, const HttpRequest& req);
	private:
		t_status	_parseRequestLine(const std::string &line);
		t_status	_parseHeaders(const std::string &req);


		std::map<std::string, std::string> _header;
		std::map<std::string, t_parseMap> _parseMap;
		std::string	_uri;
		std::string	_version;
		std::string _body;
		methods_t	_method;
};

#endif
