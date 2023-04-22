#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <netinet/in.h>
#include <string>
#include <map>
#include "http_utils.hpp"
#include "socket.hpp"

class HttpRequest
{
	public:
		HttpRequest(void);
		HttpRequest(const std::string& req, in_port_t port, char* ip);
		~HttpRequest(void);

		void setMethod(const std::string& method);
		void setUri(const std::string& uri);
		void setVersion(const std::string& version);
		void setBody(const std::string& body);
		void setQueryString(const std::string &query_string);

		inline const std::map<std::string, std::string>& getHeaders(void) const { return _header; }
		inline const std::string& getUri(void) const { return _uri; }
		inline const std::string& getIp(void) const { return _ip; }
		inline const std::string& getVersion(void) const { return _version; }
		inline const std::string& getBody(void) const { return _body; }
		inline const std::string& getQueryString(void) const { return _querystring; }
		inline const methods_t&   getMethod(void) const { return _method; }
		inline const port_t&	  getPort(void) const { return _port; }
		inline const bool&		  isBadRequest(void) const { return _badrequest; }

		friend std::ostream& operator<<(std::ostream& os, const HttpRequest& req);
	private:
		t_status	_parseRequestLine(const std::string &line);
		t_status	_parseHeaders(const std::string &req);


		std::map<std::string, std::string> _header;
		std::string _ip;
		std::string	_uri;
		std::string _querystring;
		std::string	_version;
		std::string _body;
		methods_t	_method;
		port_t		_port;
		bool		_badrequest;

};

const char	**get_http_headers(void);


#endif
