#include "http_status.hpp"

http_status_t	*get_http_status_table(size_t *size)
{
	static http_status_t	table[] = {
		{ "Continue", HTTP_STATUS_CONTINUE },
		{ "Switching Protocols", HTTP_STATUS_SWITCHING_PROT },
		{ "OK", HTTP_STATUS_OK },
		{ "Created", HTTP_STATUS_CREATED },
		{ "Accepted", HTTP_STATUS_ACCEPTED },
		{ "Non-Authoritative Information", HTTP_STATUS_NON_AUTH_INF },
		{ "No Content", HTTP_STATUS_NO_CONTENT },
		{ "Reset Content", HTTP_STATUS_RESET_CONTENT },
		{ "Multiple Choices", HTTP_STATUS_MULTIPLE_CHOICES },
		{ "Moved Permanently", HTTP_STATUS_MOVED_PERMANENTLY },
		{ "Found", HTTP_STATUS_FOUND },
		{ "See Other", HTTP_STATUS_SEE_OTHER },
		{ "Use Proxy", HTTP_STATUS_USE_PROXY },
		{ "Temporary Redirect", HTTP_STATUS_TMP_REDIRECT },
		{ "Bad Request", HTTP_STATUS_BAD_REQUEST },
		{ "Payment Required", HTTP_STATUS_PAYMENT_REQUIRED },
		{ "Forbidden", HTTP_STATUS_FORBIDDEN },
		{ "Unauthorized", HTTP_STATUS_UNAUTHORIZED},
		{ "Not Found", HTTP_STATUS_NOT_FOUND },
		{ "Method Not Allowed", HTTP_STATUS_METHOD_NOT_ALLOWED },
		{ "Not Acceptable", HTTP_STATUS_NOT_ACCEPTABLE },
		{ "Request Timeout", HTTP_STATUS_REQUEST_TIMEOUT },
		{ "Conflict", HTTP_STATUS_CONFLICT},
		{ "Gone", HTTP_STATUS_GONE },
		{ "Length Required", HTTP_STATUS_LENGTH_REQUIRED},
		{ "Payload Too Large", HTTP_STATUS_PAYLOAD_TOO_LARGE },
		{ "URI Too Long", HTTP_STATUS_URI_TOO_LONG},
		{ "Unsupported Media type", HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE },
		{ "Expectation Failed", HTTP_STATUS_EXPECTATION_FAILED },
		{ "Upgrade Required", HTTP_STATUS_UPGRADE_REQUIRED },
		{ "Internal Server Error", HTTP_STATUS_INTERNAL_SERVER_ERROR },
		{ "Not Implemented", HTTP_STATUS_NOT_IMPLEMENTED },
		{ "Bad Gateway", HTTP_STATUS_BAD_GATEWAY },
		{ "Service Unavailable", HTTP_STATUS_SERVICE_UNAVAILABLE },
		{ "Gateway Timeout", HTTP_STATUS_GATEWAY_TIMEOUT },
		{ "HTTP Version Not Supported", HTTP_STATUS_VERSION_NOT_SUPPORTED }
	};

	if (size) *size = sizeof(table)/sizeof(http_status_t);

	return (table);
}
