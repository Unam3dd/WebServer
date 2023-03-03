/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:51:04 by stales            #+#    #+#             */
/*   Updated: 2023/03/03 11:40:40 by stales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef SOCKET_HPP
#define SOCKET_HPP

//////////////////////////////////
//
//	       INCLUDES
//
/////////////////////////////////

#include <cstddef>
#include <sstream>
#include <ostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>

typedef unsigned short		uint16_t;
typedef unsigned int		uint32_t;
typedef struct sockaddr_in	sin_t;
typedef uint16_t			port_t;
typedef uint32_t			addr_t;
typedef struct protent		prot_t;
typedef unsigned char		uint8_t;

class	Socket
{
	public:

		/*
		 * 	@brief Socket Default constructor
		 */
		Socket(void);

		/*
		 * @brief Overloaded Socket constructor
		 *
		 * @param family: int (AF_INET|PF_INET|AF_INET6 etc...)
		 * @param type	: int (SOCK_STREAM | SOCK_DGRAM | SOCK_RAW)
		 * @param proto : int (IPPROTO_TCP | IPPROTO_UDP)
		 *
		 */
		Socket(int family, int type, int proto);

		/*
		 * @brief Socket Copy constructor
		 * Copy data of s in new Instantiate Socket object
		 *
		 * @param s:	Reference to another Socket Object
		 */
		Socket(const Socket& s);

		/*
		 * @brief Assignment Operator assign a new socket object
		 *
		 * @param s:	Reference to a another Socket object
		 */
		Socket	&operator=(const Socket& s);

		/*
		 *	@brief Comparator of two Socket object
		 *
		 *	@param	s: Reference to another socket
		 *
		 *	@return true if is the same file descriptor
		 *	else false
		 */
		bool	operator==(Socket& s) const;

		/*
		 *	@brief SetupSocket Methodes is call can be followed after
		 *	Default constructor it replace the Overloaded constructor
		 *
		 *	@param	family	: int (AF_INET | PF_INET | AF_INET6)
		 *	@param	type	: int (SOCK_STREAM | SOCK_DGRAM | SOCK_RAW)
		 *	@param	proto	: int (IPPROTO_TCP | IPPROTO_UDP | etc...)
		 *
		 *	@return 0 if success otherwise it is an error
		 */
		int		SetupSocket(int family, int type, int proto);

		/*
		 * @brief Getfd Inlines function is optmizied return function
		 *
		 * @return the Socket file descriptor
		 */
		inline int		Getfd(void) { return (this->_fd); }

		/*
		 * @brief Setfd Inlines function is optmizied set function
		 *
		 * @param  fd:	New fd to set
		 * @return the Socket file descriptor
		 * 
		 * @Note	Beta function maybe change later
		 */
		inline void		Setfd(int fd) { this->_fd = fd; }

		/*
		 * @brief Copy Socket information in a new Socket Object
		 *
		 * @param  fd:	New fd to set
		 * @return the Socket file descriptor
		 * 
		 * @Note	Beta function maybe change later
		 */
		inline void		CopySin(sin_t *sin) { this->_s = *sin; }


		/*
		 * @brief Connect Socket file descriptor to a Server
		 *
		 * @param	family: (AF_INET | AF_INET6 | AF_PFINET)
		 * @param	ip: is a string which represent an IP Address
		 * @param	port: is unsigned short data which represent a network port
		 *
		 * @return	0 if success and Socket file descriptor was connected to the target
		 * server, if it a nonzero value it's an error
		 *
		 * @Note Conversion of ip and port was performed in functions no need to do it !!!
		 */
		int		Connect(int family, const std::string& ip, port_t port);

		/*
		 * @brief Connect Socket file descriptor to a Server
		 *
		 * @param	family: (AF_INET | AF_INET6 | AF_PFINET)
		 * @param	address: like that (127.0.0.1:8080)
		 *
		 * @return	0 if success and Socket file descriptor was connected to the target
		 * server, if it a nonzero value it's an error
		 *
		 * @Note Conversion of ip and port was performed in functions no need to do it !!!
		 */

		int		Connect(int family, const std::string& address);
	
		/*
		 * @brief Bind Socket file descriptor to a Sockaddr_in
		 *
		 * Default is AF_INET with sin_t configuration
		 * @return	0 if success and Socket file descriptor was connected to the target
		 * server, if it a nonzero value it's an error
		 */	
		
		int 	Bind(void);

		/*
		 * @brief Bind Socket file descriptor to a Sockaddr_in
		 *
		 * @param	family: (AF_INET | AF_INET6 | AF_PFINET)
		 * @param	ip: like that (127.0.0.1)
		 * @param	port: unsigned short port (0-0xFFFF)
		 *
		 * @return	0 if success and Socket file descriptor was connected to the target
		 * server, if it a nonzero value it's an error
		 *
		 * @Note Conversion of ip and port was performed in functions no need to do it !!!
		 */
		int		Bind(int family, const std::string& ip, port_t port);
	
		/*
		 * @brief Bind Socket file descriptor to a Sockaddr_in
		 *
		 * @param	family: (AF_INET | AF_INET6 | AF_PFINET)
		 * @param	address: like that (127.0.0.1:8080)
		 *
		 * @return	0 if success and Socket file descriptor was connected to the target
		 * server, if it a nonzero value it's an error
		 *
		 * @Note Conversion of ip and port was performed in functions no need to do it !!!
		 */
		int		Bind(int family, const std::string& address);

		/*
		 * @brief Listen Socket file descriptor with configuration which was binded
		 *
		 * @param backlog: (SOMAXCONN)
		 *
		 * @return 0 if success, non zero value is an error
		 */
		int		Listen(int backlog);

		/*
		 *	@brief Accept Client from Server and create new Socket Object for the client
		 *
		 *	@return New Socket Object allocated in the heap must be freed
		 */
		Socket*	Accept(void);

		/*
		 *	@brief Accept Client from Server and create new Socket Object for the client
		 *
		 *	@param fd:	target Fd to a accept
		 *
		 *	@return New Socket Object allocated in the heap must be freed
		 */
		Socket* Accept(int fd);
	
		/*
		 *	@brief Close Client file descriptor
		 *
		 *	@param fd:	target Fd to close
		 *
		 *	@return if 0 success otherwise is an error
		 */
		int		Close(int fd);

		/*
		 *	@brief Close Client file descriptor
		 *	Close Socket file descriptor of Socket object
		 *
		 *	@return if 0 success otherwise is an error
		 */
		int		Close(void);
		
		ssize_t	Send(int fd, const void *buf, size_t len, int flags);
		ssize_t	Send(const void *buf, size_t len, int flags);
		ssize_t Send(const std::string& buf, int flags);
		ssize_t	Send(int fd, const std::string& buf, int flags);
		
		ssize_t	Recv(int fd, void *buf, size_t len, int flags);
		ssize_t	Recv(void *buf, size_t len, int flags);
		ssize_t Recv(std::string& buf, size_t len, int flags);
		ssize_t Recv(int fd, std::string& buf, size_t len, int flags);
		
		int		Write(int fd, const void *buf, size_t len);
		int		Write(const void *buf, size_t len);
		int		Write(const std::string& buf);
		int		Write(int fd, const std::string& buf);
		
		int		Read(int fd, void *buf, size_t len);
		int		Read(void *buf, size_t len);
		int		Read(std::string& buf, size_t len);
		int		Read(int fd, std::string& buf, size_t len);
		
		int		SetSockOpt(int fd, int lvl, int opt, const void *val, socklen_t len);
		int		GetSockOpt(int fd, int lvl, int opt, void *val, socklen_t *len);
		
		bool	isConnected(void);
		bool	isOnListening(void);
		bool	isBinded(void);
		bool	isCreated(void);
		
		int		SetupSin(int family, const std::string& ip, port_t port);
		void	ResetSin(void);

		addr_t	InetAddr(const std::string& ip);

		std::string	InetNtoa(addr_t addr);

		port_t		Ntohs(port_t sin_port);

		uint32_t	Htonl(uint32_t hostlong);

		uint16_t	Htons(uint16_t hostshort);

		void	Clear(void);

		prot_t	*GetProtoByName(const std::string& name);

		sin_t	*GetSin(void);

		int		Fcntl(int fd, int cmd, long arg);
		int		Fcntl(int cmd, long arg);
		
		~Socket(void);
	
	private:

		template<typename T>
		std::string			to_string(const T & value) { std::ostringstream oss; oss << value; return (oss.str()); }
		sin_t				_s;
		int					_fd;
		bool				_iscreated;
		bool				_isconnected;
		bool				_isonlistening;
		bool				_isbinded;
};

#endif
