/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:26:18 by stales            #+#    #+#             */
/*   Updated: 2023/06/19 16:13:42 by ldournoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.hpp"
#include "http_utils.hpp"
#include <cstring>
#include <fcntl.h>
#include <ostream>
#include <sys/socket.h>

/*********************************************************************
*
* @brief	Default constructor of the class Socket. Initialize the socket 
* 			without any parameters
*
* @param	void
*
* @return	void
*
*********************************************************************/
Socket::Socket(void): _fd(-1)
{
	std::memset(&_s, 0, sizeof(sin_t));
	_iscreated = false;
	_isbinded = false;
	_isconnected = false;
	_isonlistening = false;
	_forcedresponse = false;
	_forcedstatus = SANITIZE_AND_CAST_INT_TO_HTTP_STATUS(200);
}

/*********************************************************************
*
* @brief	Constructor of the class Socket. Initialize the socket with
* 			the family, type and protocol given in arg
*
* @param	family: family of the socket (AF_INET, AF_INET6, AF_UNIX)
* @param	type: type of the socket (SOCK_STREAM, SOCK_DGRAM, SOCK_RAW)
* @param	proto: protocol of the socket (IPPROTO_TCP, IPPROTO_UDP, IPPROTO_RAW)
*
* @return	void
*
*********************************************************************/
Socket::Socket(int family, int type, int proto)
{
	this->_fd = socket(family, type, proto);
	_iscreated = true;
	if (this->_fd == -1)
		_iscreated = false;
	_isbinded = false;
	_isconnected = false;
	_isonlistening = false;
	_forcedresponse = false;
	_forcedstatus = SANITIZE_AND_CAST_INT_TO_HTTP_STATUS(200);
}

/*********************************************************************
*
* @brief	Default Destructor of the class Socket. Close the socket.
*
* @param	void
*
* @return	void
*
*********************************************************************/
Socket::~Socket(void)
{
	if (this->_fd > 0)
		this->Close(_fd);
}

/*********************************************************************
*
* @brief    Assignation Operator
*
* @param    s: Socket Instance
*
* @return    Socket
*
*********************************************************************/
Socket	&Socket::operator=(const Socket& s)
{
	this->_fd = s._fd;
	this->_isonlistening = s._isonlistening;
	this->_isbinded = s._isbinded;
	this->_isconnected = s._isconnected;
	this->_iscreated = s._iscreated;
	return (*this);
}

/*********************************************************************
*
* @brief    Compare to Socket object fd
*
* @param    s: Socket Instance
*
* @return   true if fd is the same otherwise is false 
*
*********************************************************************/
bool	Socket::operator==(Socket& s) const
{
	return (this->_fd == s._fd);
}

/*********************************************************************
*
* @brief    Copy Constructor
*
* @param    s:	Socket Instance
*
* @return    Copy of Socket Object
*
*********************************************************************/
Socket::Socket(const Socket& s)
{
	this->_fd = s._fd;
	this->_isonlistening = s._isonlistening;
	this->_isbinded = s._isbinded;
	this->_isconnected = s._isconnected;
	this->_iscreated = s._iscreated;
}

/*********************************************************************
*
* @brief    SetupSocket system call
*
* @param    family: AF_INET | AF_INET6..
* @param    type: SOCK_STREAM | SOCK_DGRAM..
* @param    proto: IPPROTO_TCP | IPPROTO_UDP..
*
* @return    socket file descriptor
*
*********************************************************************/
int	Socket::SetupSocket(int family, int type, int proto)
{
	if (this->_iscreated) return (-1);
	this->_iscreated = false;
	this->_fd = socket(family, type, proto);
	if (this->_fd < 0) return (-1);
	this->_iscreated = true;
	this->_isconnected = false;
	this->_isbinded = false;
	this->_isonlistening = false;
	this->_forcedresponse = false;
	this->_forcedstatus = SANITIZE_AND_CAST_INT_TO_HTTP_STATUS(200);
	this->Fcntl(this->_fd, F_SETFD, FD_CLOEXEC);
	return (0);
}
