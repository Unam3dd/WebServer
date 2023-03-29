#include "http_status.hpp"

const char	*get_http_status_msg(http_status_code_t code)
{
	size_t	len = 0;

	http_status_t	*table = get_http_status_table(&len);

	for (size_t i = 0; i < len; i++)
		if (table[i].code == code) return (table[i].str);
	return (NULL);
}
