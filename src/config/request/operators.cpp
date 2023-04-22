/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 22:03:40 by ldournoi          #+#    #+#             */
/*   Updated: 2023/04/22 19:46:58 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_request_config.hpp"
#include "http_utils.hpp"

std::ostream	&operator<<(std::ostream& os, HttpRequestConfig& sc)
{
	std::vector <std::string> tmp;
	std::map<std::string, std::string> cgi;
	os << "\t\tRequestConfig: "  << sc.GetScope() << std::endl;
	tmp = sc.GetIndexs();
	sc.GetHttpResponseCode() == 0 ? os << "\t\t\tResponse code: 200" << std::endl : os << "\t\t\tResponse code: " << sc.GetHttpResponseCode() << std::endl;
	os << "\t\t\tIndexes: "; PRINT_VECTOR_STR(tmp, os); os << std::endl;
	os << "\t\t\tRoot: " << sc.GetRoot() << std::endl;
	os << "\t\t\tUpload: " << sc.GetUploads() << std::endl;
	os << "\t\t\tMaxPostSize: " << sc.GetMaxPostSize() << std::endl;
	os << "\t\t\tCookies: " << sc.GetCookies() << std::endl;
	os << "\t\t\tMethods: "; sc.GetMethods() & GET ? os << "GET " : os; sc.GetMethods() & POST ? os << "POST " : os; sc.GetMethods() & PUT ? os << "PUT " : os; sc.GetMethods() & DELETE ? os << "DELETE " : os; os << std::endl;
	cgi = sc.GetCgi();
	os << "\t\t\tCGI: "; PRINT_MAP_STR(cgi, os); os << std::endl;
	os << "\t\t\tError pages: " << std::endl;
	for (size_t i = 0; i < MAX_ERR_PAGES; i++)
		os << "\t\t\t\t" << sc.GetErrorPages()[i].code << " -> " << sc.GetErrorPages()[i].path << std::endl;
	return (os);
}
