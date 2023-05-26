/*#BEGIN#_________________________>#_|INFO|_#<______________________________##*/
/*#                                                        ______ _         ##*/
/*# DETAILS:                                               | ___ (_)        ##*/
/*#- FILENAME		Logger.hpp                             | |_/ /___  __   ##*/
/*#- PROJECT_NAME	None                                   |  __/| \ \/ /   ##*/
/*#- AUTHOR			Pixailz                                | |   | |>  <    ##*/
/*#- CREATED		2023−01−29T23:02:00+0100               \_|   |_/_/\_\   ##*/
/*#                                                                         ##*/
/*#END#___________________________<#_|INFO|_#>______________________________##*/

#ifndef LOGGER_HPP
# define LOGGER_HPP

#include <iostream>
/**
 * <object>		std::cout
 * <object>		std::endl
 */

#include <unistd.h>
/**
 * <func>		write()
 * <func>		close()
 */
#include <sstream>
/**
 * <func>		ostringstream()
 */

# ifndef	DEBUG
#  define	DEBUG					0
# endif

# ifndef	DEBUG_FD
#  define	DEBUG_FD				420
# endif

# ifndef	VERBOSE
#  define	VERBOSE					1
# endif

# define	ANSI_ESC				"\x1b["
# define	R						ANSI_ESC "38:2::255:0:0m"
# define	G						ANSI_ESC "38:2::0:255:0m"
# define	B						ANSI_ESC "38:2::0:0:255m"
# define	C						ANSI_ESC "38:2::0:255:255m"
# define	RST						ANSI_ESC "0m"

# define	H_I						"[" C "INFO " RST "]"
# define	H_D						"[" C "DEBUG" RST "]"
# define	H_E						"[" R "ERROR" RST "]"

# define	FUNC_POS				"50"
# define	GOTO_FUNC				ANSI_ESC FUNC_POS "G"

# define	ANSI_FMT(color, str)	(color str RST)

# define	G_SRV_BLK				G "srvblk::" RST
# define	G_LOC_BLK				G "locblk" RST
# define	R_SRV_BLK				R "!srvblk::" RST
# define	R_LOC_BLK				R "!locblk" RST

class Logger
{
	private:
		// ATRIBUTS
		std::string			_header;
		std::string			_caller_info;

		void				set_header(std::string);
		void				set_caller_info(std::string caller_func,
			std::string caller_file,
			int caller_line);
		std::string			get_header(void);
		std::string			get_caller_info(void);

		void				info(std::string str);
		void				error(std::string str);
		void				debug(std::string str);

		void				format(std::string str);
		void				write_fd(int fd, std::string str);
		void				write_debug_fd(int fd, std::string str, std::string header, std::string caller_info);
	public:

		// CONSTRUCTOR(S)
		Logger(void);
		Logger(const Logger &copy);
		// DESTRUCTOR(S)
		~Logger(void);
		// OPERATOR(S) FUNCTION
		Logger				&operator=(const Logger &src);

		// OTHERS
		std::string			itoa(int nstr);
		void				log(int mode, std::string str,
			std::string caller_func = __builtin_FUNCTION(),
			std::string caller_file = __builtin_FILE(),
			int caller_line = __builtin_LINE());
};

static Logger logz = Logger();

#endif // LOGGER_CLASS
