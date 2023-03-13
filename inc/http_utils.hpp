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
