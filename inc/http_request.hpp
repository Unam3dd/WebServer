#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <map>
#include "http_utils.hpp"

class HttpRequest
{
	public:
		HttpRequest(void);
		HttpRequest(const std::string& req);
		~HttpRequest(void);

		void setMethod(const std::string& method);
		void setUri(const std::string& uri);
		void setVersion(const std::string& version);
		void addHeader(const std::string& key, const std::string& value);
		void setBody(const std::string& body);

		inline const std::map<std::string, std::string>& getHeaders(void) const { return _header; }
		inline const std::string& getMethod(void) const { return _method; }
		inline const std::string& getUri(void) const { return _uri; }
		inline const std::string& getVersion(void) const { return _version; }
		inline const std::string& getBody(void) const { return _body; }
	private:
		t_status	_parseRequestLine(const std::string &line);


		std::map<std::string, std::string> _header;
		std::string	_method;
		std::string	_uri;
		std::string	_version;
		std::string _body;
};

#endif
