#include "http_response.hpp"
#include "http_utils.hpp"

/*
 * @brief: not proud of this one. return the content type for the given file
 * extension using a singleton map.
 *
 * @param: path: the path of the file for which to get the content type.
 *
 * @return: the content type for the given file extension.
 * 
 */
std::string HttpResponse::_getContentType(const std::string& path){
	std::string extension = path.substr(path.find_last_of("."), path.length() - path.find_last_of("."));

	return (SG_GetContentType(extension));
}
