/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 22:03:40 by ldournoi          #+#    #+#             */
/*   Updated: 2023/03/19 09:52:12 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_config.hpp"
#include "http_utils.hpp"
#include "socket.hpp"

std::ostream	&operator<<(std::ostream& os, HttpServerConfig& sc)
{
	os << "HttpServerConfig: "; PRINT_VECTOR_STR(static_cast < std::vector < std::string > >(sc.GetServerNames()), os); os << std::endl;
	os << "\t\tPort: "; PRINT_VECTOR_PORTS(static_cast < std::vector < port_t > >(sc.GetServerPorts()), os); os << std::endl;
	os << "\t\tIndexes: "; PRINT_VECTOR_STR(static_cast < std::vector < std::string > >(sc.GetIndexs()), os); os << std::endl;
	os << "\t\tRoot: " << sc.GetRoot() << std::endl;
	os << "\t\tUpload: " << sc.GetUploads() << std::endl;
	os << "\t\tUploaddir: " << sc.GetUploadDir() << std::endl;
	os << "\t\tCGI: "; PRINT_VECTOR_STR(static_cast < std::vector < std::string > >(sc.GetCgi()), os); os << std::endl;
	os << "\t\tError pages: " << std::endl;
	for (size_t i = 0; i < MAX_ERR_PAGES; i++)
		os << "\t\t\t" << sc.GetErrorPages()[i].code << " -> " << sc.GetErrorPages()[i].path << std::endl;
	os << "\t\tRedirections: " << sc.GetRedirections().size() << std::endl;
	for (size_t i = 0; i < sc.GetRedirections().size(); i++)
		os << "\t\t\t" << sc.GetRedirections()[i].path << " -> " << sc.GetRedirections()[i].dest << "(" << sc.GetRedirections()[i].code << ")" << std::endl;
	os << "\t\tNumber of locations: " << sc.GetRequestConfigs().size() << std::endl;
	for (size_t i = 0; i < sc.GetRequestConfigs().size(); i++)
		os << sc.GetRequestConfigs()[i];
	return (os);
}
