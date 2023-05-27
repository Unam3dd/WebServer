#pragma once
#ifndef HTTP_UTILS_HPP
#define HTTP_UTILS_HPP

#include "file.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <unistd.h>
#include <fcntl.h>

//////////////////////////////////
//
//	       DEFINES
//
/////////////////////////////////

#define VERSION "1.0.0"
#define MAX_EVENT 16

#define FOREACH_VECTOR(type, variable, it) for(std::vector<type>::iterator it = variable.begin(); it < variable.end(); it++)
#define FOREACH_VECTOR_CONST(type, variable, it) for(std::vector<type>::const_iterator it = variable.begin(); it < variable.end(); it++)
#define FOREACH_MAP_STR(x, y) for (std::map<std::string, std::string>::iterator y = x.begin(); y != x.end(); ++y)
#define FOREACH_MAP_STR_CONST(x, y) for (std::map<std::string, std::string>::const_iterator y = x.begin(); y != x.end(); ++y)

#define APPEND_FILE_TO_STRING(str, file) for (file_size_t i = 0; i < file.length(); i++) str += file.getData()[i];
#define IS_BAD_IP(x) (check_format_ip(x) == false)
#define FILE_EXISTS(x) (File(x, O_RDONLY, S_IRUSR).getFd() != -1)
#define SANITIZE_AND_CAST_INT_TO_HTTP_STATUS(status) ((status < 100 || status > 102) && (status < 200 || status > 208) && (status < 300 || status > 308) && (status < 400 || status > 417) && (status < 500 || status > 505) ? HTTP_STATUS_INTERNAL_SERVER_ERROR : static_cast<http_status_code_t>(status))

#define COUNT_SPACES(x) (std::count(x.begin(), x.end(), ' ') + std::count(x.begin(), x.end(), '\t'))
#define SANITIZE_SPACES(x) x.erase(std::remove(x.begin(), x.end(), ' '), x.end()); x.erase(std::remove(x.begin(), x.end(), '\t'), x.end())

#define PRINT_VECTOR_STR(x,y) for (std::vector<std::string>::iterator it = x.begin(); it != x.end(); ++it) y << *it << " ";
#define PRINT_VECTOR_PORTS(x,y) for (std::vector<port_t>::iterator it = x.begin(); it != x.end(); ++it) y << *it << " ";
#define PRINT_MAP_STR(x, y) for (std::map<std::string, std::string>::iterator it = x.begin(); it != x.end(); ++it) y << it->first << " -> " << it->second << " ";

#define LOWERCASE(x) std::transform(x.begin(), x.end(), x.begin(), ::tolower);
#define UPPERCASE(x) std::transform(x.begin(), x.end(), x.begin(), ::toupper);

#define STR_METHOD(x) (x == GET ? "GET" : x == POST ? "POST" : x == PUT ? "PUT" : x == DELETE ? "DELETE" : "UNKNOWN")

#define MAX_ERR_PAGES 0xc
#define IPV4_BYTES_LEN 0x4
#define IPV4_BITS_LEN 0x20
//////////////////////////////////
//
//	       TYPEDEFS
//
/////////////////////////////////

typedef unsigned int	maxpost_size_t;

//////////////////////////////////
//
//	       ENUM
//
/////////////////////////////////

enum methods_t
{
	GET = 1 << 0,
	POST = 1 << 1,
	PUT = 1 << 2,
	DELETE = 1 << 3,
	UNKNOWN = 1 << 4
};

enum t_errcode {
	ERRPARSE_OK = 0,
	ERRPARSE_UNKNOWN,
	ERRPARSE_NEWSRVBLK,
	ERRPARSE_NEWLOCBLK,
	ERRPARSE_ENDBLK,
	ERRPARSE_SINGLEARG,
	ERRPARSE_NOARG,
	ERRPARSE_PORT,
	ERRPARSE_ERRPAGE,
	ERRPARSE_SPCORTAB,
	ERRPARSE_DUP,
	ERRPARSE_POST,
	ERRPARSE_TIMEOUT,
	ERRPARSE_COOKIES,
	ERRPARSE_UPLOADS,
	ERRPARSE_DIRLIST,
	ERRPARSE_CGI,
	ERRPARSE_METHODS,
	ERRPARSE_UPLOADDIR,
	ERRPARSE_NBARGS,
	ERRPARSE_NOSRVNAME,
	ERRPARSE_NOPORT,
	ERRPARSE_HTTPCODE
};
typedef std::map<t_errcode, std::string> errcodestr_t;

enum t_status
{
	STATUS_OK,
	STATUS_FAIL
};

typedef enum {
	E400 = 0,
	E401 = 1,
	E403 = 2,
	E404 = 3,
	E405 = 4,
	E408 = 5,
	E411 = 6,
	E413 = 7,
	E500 = 8,
	E501 = 9,
	E502 = 10,
	E505 = 11
} errpagecode_t;

//////////////////////////////////
//
//		   SINGLETONS
//
/////////////////////////////////
class WebServer;
WebServer *SG_WebServer(const WebServer* ws);

std::string	SG_GetContentType(std::string& extension);
std::string	SG_DefaultErrorPages(errpagecode_t status);

char**	SG_ENVP(char **envp);

//////////////////////////////////
//
//	       STRUCTS
//
/////////////////////////////////

struct errpage_t
{
	std::string		path;
	int				code;
};

/*
 * @brief Check format of Ipv4 address
 *
 * @param ip: const std::string& like "127.0.0.1"
 *
 * @return true if is valid else is false
 */
bool	check_format_ip(const std::string& ip);

#endif
