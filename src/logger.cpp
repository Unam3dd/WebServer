/*#BEGIN#_________________________>#_|INFO|_#<______________________________##*/
/*#                                                        ______ _         ##*/
/*# DETAILS:                                               | ___ (_)        ##*/
/*#- FILENAME		Logger.cpp                               | |_/ /___  __   ##*/
/*#- PROJECT_NAME	None                                   |  __/| \ \/ /   ##*/
/*#- AUTHOR			Pixailz                                | |   | |>  <    ##*/
/*#- CREATED		2023−01−29T23:02:00+0100               \_|   |_/_/\_\   ##*/
/*#                                                                         ##*/
/*# DESCRIPTION:                                                            ##*/
/*## None                                                                   ##*/
/*#                                                                         ##*/
/*# VERSION:[ALPHA|BETA]_MAJOR.MINOR.PATCH                                  ##*/
/*#END#___________________________<#_|INFO|_#>______________________________##*/

# include <logger.hpp>
/**
 * <object>		object
 * <function>	function()
 */

Logger::Logger(void) {}

Logger::~Logger(void)
{
	close(DEBUG_FD);
}

Logger::Logger(const Logger &copy)
{
	*this = copy;
}

Logger	&Logger::operator=(const Logger &src)
{
	(void)src;
	return (*this);
}


std::string	Logger::itoa(int nstr)
{
	std::ostringstream	buff;

	buff << nstr;
	return (buff.str());
}

void	Logger::set_caller_info(std::string caller_func,
	std::string caller_file,
	int caller_line)
{
	std::string	tmp;

	tmp = "[";
	tmp += caller_func;
	tmp += ";";
	tmp += this->itoa(caller_line);
	tmp += ":";
	tmp += caller_file;
	tmp += "]";
	this->_caller_info = tmp;
}

void	Logger::set_header(std::string header)
{
	this->_header = header;
}

std::string	Logger::get_caller_info(void)
{
	return (this->_caller_info);
}

std::string	Logger::get_header(void)
{
	return (this->_header);
}

void	Logger::write_fd(int fd, std::string str)
{
	write(fd, str.c_str(), str.length());
}

void	Logger::write_debug_fd(int fd, std::string str, std::string header, std::string caller_info)
{
	this->write_fd(fd, header + " ");
	if (fd == DEBUG_FD)
	{
		this->write_fd(fd, caller_info);
		this->write_fd(fd, GOTO_FUNC);
	}
	this->write_fd(fd, str);
	this->write_fd(fd, "\n");
}

void	Logger::format(std::string str)
{
	std::string caller_info = this->get_caller_info();
	std::string header = this->get_header();

	#if DEBUG != 0
		this->write_debug_fd(1, str, header, caller_info);
	#endif
	this->write_debug_fd(DEBUG_FD, str, header, caller_info);
}

void	Logger::log(int mode, std::string str,
			std::string caller_func,
			std::string caller_file,
			int caller_line)
{
	this->set_caller_info(caller_func, caller_file, caller_line);
	switch (mode)
	{
		case 0:	this->info(str); break;
		case 1:	this->debug(str); break;
		case 2:	this->error(str); break;
	}
}

void	Logger::info(std::string str)
{
	this->set_header(H_I);
	this->format(str);
}

void	Logger::error(std::string str)
{
	this->set_header(H_E);
	this->format(str);
}

void	Logger::debug(std::string str)
{
	this->set_header(H_D);
	this->format(str);
}

