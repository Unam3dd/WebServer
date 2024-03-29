#include "http_headers.hpp"

const char**	get_http_headers(void)
{
	static const char* http_headers[] = {
		"accept",
		"accept-charset",
		"accept-encoding",
		"accept-language",
		"accept-ranges",
		"age",
		"allow",
		"authorization",
		"cache-control",
		"connection",
		"content-encoding",
		"content-language",
		"content-length",
		"content-location",
		"content-md5",
		"content-range",
		"content-type",
		"cookie",
		"date",
		"etag",
		"expect",
		"expires",
		"from",
		"host",
		"if-match",
		"if-modified-since",
		"if-none-match",
		"if-range",
		"if-unmodified-since",
		"last-modified",
		"location",
		"max-forwards",
		"pragma",
		"proxy-authenticate",
		"proxy-authorization",
		"range",
		"referer",
		"retry-after",
		"server",
		"te",
		"trailer",
		"transfer-encoding",
		"upgrade",
		"user-agent",
		"vary",
		"via",
		"warning",
		"www-authenticate",
		NULL
	};
	
	return (http_headers);
}
