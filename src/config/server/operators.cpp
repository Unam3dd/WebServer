/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 22:03:40 by ldournoi          #+#    #+#             */
/*   Updated: 2023/03/20 01:52:36 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config.hpp"
#include "http_utils.hpp"
#include "socket.hpp"

std::ostream	&operator<<(std::ostream& os, HttpServerConfig& sc)
{
	std::map<std::string, std::string> cgi;
	std::vector<std::string> tmp;
	std::vector<port_t> ports = sc.GetServerPorts();
	std::vector<HttpRequestConfig> locations = sc.GetRequestConfigs();

	tmp = sc.GetServerNames();
	os << "HttpServerConfig: "; PRINT_VECTOR_STR(tmp, os); os << std::endl;
	os << "\t\tPort: "; PRINT_VECTOR_PORTS(ports, os); os << std::endl;
	tmp = sc.GetIndexs();
	os << "\t\tIndexes: "; PRINT_VECTOR_STR(tmp, os) os << std::endl;
	os << "\t\tRoot: " << sc.GetRoot() << std::endl;
	os << "\t\tUpload: " << sc.GetUploads() << std::endl;
	os << "\t\tUploaddir: " << sc.GetUploadDir() << std::endl;
	os << "\t\tMethods: "; sc.GetMethods() & GET ? os << "GET " : os; sc.GetMethods() & POST ? os << "POST " : os; sc.GetMethods() & PUT ? os << "PUT " : os; sc.GetMethods() & DELETE ? os << "DELETE " : os; os << std::endl;
	//os << "\t\tSessionPath: " << sc.GetSessionPath() << std::endl;
	os << "\t\tTimeout: " << sc.GetServerTimeout() << std::endl;
	os << "\t\tMaxPostSize: " << sc.GetMaxPostSize() << std::endl;
	os << "\t\tCookies: " << sc.GetCookies() << std::endl;
	os << "\t\tDir Listing: " << sc.GetDirList() << std::endl;
	cgi = sc.GetCgi();
	os << "\t\tCGI: "; PRINT_MAP_STR(cgi, os) os << std::endl;
	os << "\t\tError pages: " << std::endl;
	for (size_t i = 0; i < MAX_ERR_PAGES; i++)
		os << "\t\t\t" << sc.GetErrorPages()[i].code << " -> " << sc.GetErrorPages()[i].path << std::endl;
	os << "\t\tRedirections: " << sc.GetRedirections().size() << std::endl;
	for (size_t i = 0; i < sc.GetRedirections().size(); i++)
		os << "\t\t\t" << sc.GetRedirections()[i].path << " -> " << sc.GetRedirections()[i].dest << "(" << sc.GetRedirections()[i].code << ")" << std::endl;
	os << "\t\tNumber of locations: " << locations.size() << std::endl;
	for (size_t i = 0; i < locations.size(); i++)
		os << locations[i];
	return (os);
}
