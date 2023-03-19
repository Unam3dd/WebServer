/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 22:03:40 by ldournoi          #+#    #+#             */
/*   Updated: 2023/03/19 09:41:56 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_request_config.hpp"
#include "http_utils.hpp"
#include "socket.hpp"

std::ostream	&operator<<(std::ostream& os, HttpRequestConfig& sc)
{
	os << "\t\tRequestConfig: "  << sc.GetScope() << std::endl;
	//os << "\t\tMethods: "; PRINT_VECTOR_STR(static_cast < std::vector < method_t > >(sc.GetMethods()), os); os << std::endl;
	os << "\t\t\tCGI: "; PRINT_VECTOR_STR(static_cast < std::vector < std::string > >(sc.GetCgi()), os); os << std::endl;
	os << "\t\t\tIndexes: "; PRINT_VECTOR_STR(static_cast < std::vector < std::string > >(sc.GetIndexs()), os); os << std::endl;
	os << "\t\t\tRoot: " << sc.GetRoot() << std::endl;
	os << "\t\t\tUpload: " << sc.GetUploads() << std::endl;
	os << "\t\t\tUploaddir: " << sc.GetUploadDir() << std::endl;
	//os << "\t\tError pages: " << sc.GetErrorPages().size() << std::endl;
	//for (size_t i = 0; i < sc.GetErrorPages().size(); i++)
	//	os << "\t\t\t" << sc.GetErrorPages()[i].first << " -> " << sc.GetErrorPages()[i].second << std::endl;
	//os << "\t\tRedirections: " << sc.GetRedirections().size() << std::endl;
	//for (size_t i = 0; i < sc.GetRedirections().size(); i++)
	//	os << "\t\t\t" << sc.GetRedirections()[i].first << " -> " << sc.GetRedirections()[i].second << std::endl;

	return (os);
}
