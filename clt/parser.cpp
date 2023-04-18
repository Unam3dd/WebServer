#include "http_client.hpp"
#include <cstring>
#include <cstdlib>
#include <iostream>

ParseURL::ParseURL(void)
{
}

ParseURL::~ParseURL(void)
{
}

ParseURL::ParseURL(const std::string &url)
{
	if (this->_ParseURL(url))
		std::cerr << "Error: failed to parse URL !" << std::endl;
}

int	ParseURL::_ParseURL(const std::string& url)
{
	std::string	tmp;
	hostent		*hst = NULL;
	size_t		pos = 0;

	if (url.empty()) return (1);

	pos = url.find(":");
	if (pos == std::string::npos || (pos != 4 && pos != 5)) return (1);

	tmp = url.substr(0, pos);
	if (std::strspn(tmp.c_str(), ":") > 1) return (1);

	if (tmp.empty() || (tmp != "http" && tmp != "https")) return (1);

	_proto = (tmp == "https") ? HTTPS_PROTOCOL : HTTP_PROTOCOL;

	tmp = (url.c_str() + pos);

	if (tmp.substr(0, 3) != "://" || std::strspn(tmp.c_str(), "://") > 3) return (1);

	pos += 3;
	tmp = (url.c_str() + pos);

	pos = tmp.find(":");

	if (pos == std::string::npos) {
		_host = tmp.substr(0, tmp.find("/"));
		_port = (_proto == HTTPS_PROTOCOL) ? HTTPS_DEFAULT_PORT : HTTP_DEFAULT_PORT;
		pos += _host.length();
	} else {
		if (std::strspn(tmp.c_str()+pos+1, ":") > 1) return (1);
		_host = tmp.substr(0, pos);
		_port = std::atoi(tmp.substr(pos+1, tmp.find("/")).c_str());
		pos += std::strspn(tmp.substr(pos+1).c_str(), "0123456789");
	}
	_uri = (tmp.c_str() + pos + 1);
	
	if (_uri.empty()) _uri = "/";

	if (!isIP(_host)) {
		hst = gethostbyname(_host.c_str());
		_ip = inet_ntoa(*(in_addr*)hst->h_addr_list[0]);
	} else _ip = _host;

	return (0);
}

bool	ParseURL::isIP(const std::string& str)
{
	char		*tmp = NULL;
	size_t		pos = 0;
	int			digits = 0;
	int			dot = 0;

	if (str.empty() || (str.length() < 0x7 || str.length() > 0xF)) return (false);
	tmp = const_cast<char*>(str.c_str());
	while (*tmp) {
		pos = std::strspn(tmp, "0123456789");

		if (!pos || pos > 3) return (false);
		
		digits = std::atoi(tmp);

		if (digits < 0 || digits > 0xFF) return (false);
		
		if (dot > 3 || std::strspn(tmp+pos, ".") > 1) return (false);

		if (std::strspn(tmp+pos, ".")) {
			dot++;
			pos++;
		}

		tmp += pos;
	}
	return (true);
}
