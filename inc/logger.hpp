/*#BEGIN#_________________________>#_|INFO|_#<______________________________##*/
/*#                                                        ______ _         ##*/
/*# DETAILS:                                               | ___ (_)        ##*/
/*#- FILENAME		Logger.hpp                             | |_/ /___  __   ##*/
/*#- PROJECT_NAME	WebServer                              |  __/| \ \/ /   ##*/
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
# define	Y						ANSI_ESC "38:2::255:255:0m"
# define	O						ANSI_ESC "38:2::255:165:0m"
# define	RST						ANSI_ESC "0m"

# define	H_I						"[" C "INFO " RST "]"
# define	H_D						"[" C "DEBUG" RST "]"
# define	H_W						"[" O "WARN " RST "]"
# define	H_P						"[" G "PASS " RST "]"
# define	H_E						"[" R "ERROR" RST "]"

# define	INFO_LEN				38
# define	INFO_POS				"50"
# define	GOTO_FUNC				ANSI_ESC INFO_POS "G"

# define	ANSI_FMT(color, str)	(color str RST)

typedef enum e_log_type
{
	L_INFO		= 1 << 0,
	L_DEBUG		= 1 << 1,
	L_WARN		= 1 << 2,
	L_PASS		= 1 << 3,
	L_ERROR		= 1 << 4,
	L_BYPASS	= 1 << 5
}	t_log_type;

class Logger
{
	private:
		// ATRIBUTS
		std::string			_header;
		std::string			_caller_info;
		bool				_bypass;

		void				set_header(std::string);
		void				set_caller_info(std::string caller_func,
			std::string caller_file,
			int caller_line);
		void				set_bypass(bool val);

		std::string			get_header(void);
		std::string			get_caller_info(void);
		bool				get_bypass(void);

		void				info(int fd, std::string str);
		void				debug(int fd, std::string str);
		void				warn(int fd, std::string str);
		void				pass(int fd, std::string str);
		void				error(int fd, std::string str);

		void				format(int fd, std::string str);
		void				prep_format(int mode, int fd, std::string str);
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
		std::string			boolean(bool value);
		std::string			get_methods(int	methods);

		void				log(int mode, std::string str,
								std::string caller_func = __builtin_FUNCTION(),
								std::string caller_file = __builtin_FILE(),
								int caller_line = __builtin_LINE());
		void				logerr(int mode, std::string str,
								std::string caller_func = __builtin_FUNCTION(),
								std::string caller_file = __builtin_FILE(),
								int caller_line = __builtin_LINE());
};

static Logger logz = Logger();

#endif // LOGGER_CLASS
