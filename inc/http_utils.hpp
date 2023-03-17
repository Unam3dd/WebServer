#pragma once
#ifndef HTTP_UTILS_HPP
#define HTTP_UTILS_HPP

#include <string>

//////////////////////////////////
//
//	       DEFINES
//
/////////////////////////////////

#define IS_BAD_IP(x) (check_format_ip(x) == false)
#define IPV4_BYTES_LEN 0x4
#define IPV4_BITS_LEN 0x20

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
	DELETE = 1 << 2
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
	ERRPARSE_ERRPAGE
} t_errcode;

typedef enum {
	E400 = 0,
	E401 = 1,
	E403 = 3,
	E404 = 4,
	E405 = 5,
	E500 = 6,
	E501 = 7,
	E505 = 8
} t_errpages;


//////////////////////////////////
//
//	       STRUCTS
//
/////////////////////////////////

struct errpage_t
{
	std::string		path;
	errcode_t		code;
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
