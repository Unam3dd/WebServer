/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isdirectory.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldournoi <ldournoi@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:10:10 by ldournoi          #+#    #+#             */
/*   Updated: 2023/04/09 19:14:14 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_response.hpp"
#include <cstring>
#include <sys/stat.h>
#include <iostream>

/*
 * @brief: check if the given path is a directory.
 * if the path is a directory, check if the directory contains an index file.
 * if the directory contains an index file, set the path to the index file.
 *
 * @param: path: the path to check.
 *
 * @return: true if the given path is a directory, false otherwise.
 * if the path is a directory, check if the directory contains an index file.
 * if the directory contains an index file, set the path to the index file,
 * and return false.
 *
 */

bool	HttpResponse::_isDirectory(std::string& path){
	struct stat st;

	std::memset(&st, 0, sizeof(st));
	stat(path.c_str(), &st);
	if (FILE_EXISTS(path.c_str()) || !S_ISDIR(st.st_mode))
		return false;
	else if (*path.rbegin() == '/' && FILE_EXISTS((path.substr(0, path.length() - 1).c_str()))){
		path = path.substr(0, path.length() - 1);
		return false;
	}
	else if (_reqcfg && _reqcfg->GetIndexs().size() > 0)
	{
		FOREACH_VECTOR_CONST(std::string, _reqcfg->GetIndexs(), index){
			if (FILE_EXISTS((path + *index).c_str()))
			{
				path += *index;
				return false;
			}
		}
	}
	else if (_srvcfg->GetIndexs().size() > 0)
	{
		FOREACH_VECTOR_CONST(std::string, _srvcfg->GetIndexs(), index){
			if (FILE_EXISTS((path + *index).c_str()))
			{
				path += *index;
				return false;
			}
		}
	}
	return true;
}
