#pragma once
#ifndef HTTP_UTILS_HPP
#define HTTP_UTILS_HPP

#include <string>
#include <vector>
#include <algorithm>
//////////////////////////////////
//
//	       DEFINES
//
/////////////////////////////////

#define IS_BAD_IP(x) (check_format_ip(x) == false)
#define IPV4_BYTES_LEN 0x4
#define IPV4_BITS_LEN 0x20

#define PRINT_VECTOR_STR(x,y) for (std::vector<std::string>::iterator it = x.begin(); it != x.end(); ++it) y << *it << " ";
#define PRINT_VECTOR_PORTS(x,y) for (std::vector<port_t>::iterator it = x.begin(); it != x.end(); ++it) y << *it << " ";
#define PRINT_MAP_STR(x, y) for (std::map<std::string, std::string>::iterator it = x.begin(); it != x.end(); ++it) y << it->first << " -> " << it->second << " ";
#define LOWERCASE(x) std::transform(x.begin(), x.end(), x.begin(), ::tolower);
#define MAX_ERR_PAGES 0x8

//////////////////////////////////
//
//	       TYPEDEFS
//
/////////////////////////////////

typedef unsigned int	timeout_t;
typedef unsigned int	errcode_t;
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
	DELETE = 1 << 3
};

typedef enum {
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
	ERRPARSE_NOPORT
} t_errcode;

typedef enum {
	E400 = 0,
	E401 = 1,
	E403 = 2,
	E404 = 3,
	E405 = 4,
	E500 = 5,
	E501 = 6,
	E505 = 7
} errpagecode_t;


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

struct redirect_t
{
	std::string		path;
	std::string		dest;
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
