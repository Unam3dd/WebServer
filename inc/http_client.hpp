#ifndef HTTP_CLIENT_HPP
#define HTTP_CLIENT_HPP

#include <string>
#include "http_status.hpp"
#include "libsocket/socket.hpp"

#define HTTP_DEFAULT_PORT 80
#define HTTPS_DEFAULT_PORT 443
#define HTTP_VERSION "HTTP/1.1"

enum http_proto_t
{
	HTTP_PROTOCOL,
	HTTPS_PROTOCOL
};

enum http_method_t
{
	GET,
	POST,
	PUT,
	DELETE
};

class ParseURL
{
	public:
		ParseURL(void);
		ParseURL(const std::string& url);
		~ParseURL(void);
		int								_ParseURL(const std::string& url);
		bool							isIP(const std::string& str);
		inline http_proto_t				GetProto(void) const { return (_proto); }
		inline const std::string&		GetIP(void) const { return (_ip); }
		inline const std::string&		GetUri(void) const { return (_uri); }
		inline port_t					GetPort(void) { return (_port); }
	
	protected:
		http_proto_t		_proto;
		std::string			_ip;
		std::string			_host;
		port_t				_port;
		std::string			_uri;
};

class HttpClient
{
	public:
		HttpClient(void);
		~HttpClient(void);

		inline const Socket&			GetSocket(void) { return (_s); }
		inline http_status_code_t		GetStatusCode(void) { return (_status); }
		http_status_code_t				get(const std::string& url);
		http_status_code_t				post(const std::string& url, const std::string& body);
		http_status_code_t				del(const std::string& url, const std::string& filename);
	
	protected:
		Socket				_s;
		ParseURL			_url;
		http_status_code_t	_status;
};

class RequestFormatter
{
	public:
		RequestFormatter(void);
		RequestFormatter(ParseURL& url, http_method_t method);
		~RequestFormatter(void);
	
	private:
		const char	*get_string_method(http_method_t method);
};

#endif
