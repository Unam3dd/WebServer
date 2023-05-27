/*#BEGIN#_________________________>#_|INFO|_#<______________________________##*/
/*#                                                        ______ _         ##*/
/*# DETAILS:                                               | ___ (_)        ##*/
/*#- FILENAME		Logger.cpp                             | |_/ /___  __   ##*/
/*#- PROJECT_NAME	WebServer                              |  __/| \ \/ /   ##*/
/*#- AUTHOR			Pixailz                                | |   | |>  <    ##*/
/*#- CREATED		2023−01−29T23:02:00+0100               \_|   |_/_/\_\   ##*/
/*#                                                                         ##*/
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


std::string	Logger::get_methods(int methods)
{
	std::string	tmp = "";

	if (methods & 0b1)
		tmp += "GET ";
	if (methods & 0b10)
		tmp += "POST ";
	if (methods & 0b100)
		tmp += "PUT ";
	if (methods & 0b1000)
		tmp += "DELETE ";
	if (methods & 0b10000)
		tmp += "UNKNOWN";
	return (tmp);
}

std::string	Logger::boolean(bool value)
{
	return (value ? G "True" RST : R "False" RST);
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

	tmp = caller_func;
	tmp += ";";
	tmp += this->itoa(caller_line);
	tmp += ":";
	tmp += caller_file;
	if (tmp.length() <= INFO_LEN)
		this->_caller_info = "[" + tmp + "]";
	else
		this->_caller_info = "[" + tmp.substr(0, INFO_LEN - 2) + ".." + "]";
}

void	Logger::set_header(std::string header)
{
	this->_header = header;
}

void	Logger::set_bypass(bool val)
{
	this->_bypass = val;
}

std::string	Logger::get_caller_info(void)
{
	return (this->_caller_info);
}

std::string	Logger::get_header(void)
{
	return (this->_header);
}

bool	Logger::get_bypass(void)
{
	return (this->_bypass);
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

void	Logger::format(int fd, std::string str)
{
	std::string caller_info = this->get_caller_info();
	std::string header = this->get_header();

	#if DEBUG != 0
		this->write_debug_fd(fd, str, header, caller_info);
	#endif
	if (this->get_bypass())
		this->write_debug_fd(fd, str, header, caller_info);
	this->write_debug_fd(DEBUG_FD, str, header, caller_info);
}

void	Logger::prep_format(int mode, int fd, std::string str)
{
	if (mode & L_BYPASS)
	{
		this->set_bypass(true);
		mode -= L_BYPASS;
	}
	switch (mode)
	{
		case L_INFO:	this->info(fd, str); break;
		case L_DEBUG:	this->debug(fd, str); break;
		case L_WARN:	this->warn(fd, str); break;
		case L_PASS:	this->pass(fd, str); break;
		case L_ERROR:	this->error(fd, str); break;
	}
	if (this->get_bypass())
		this->set_bypass(false);
}

void	Logger::log(int mode, std::string str,
			std::string caller_func,
			std::string caller_file,
			int caller_line)
{
	this->set_caller_info(caller_func, caller_file, caller_line);
	this->prep_format(mode, 1, str);
}

void	Logger::logerr(int mode, std::string str,
			std::string caller_func,
			std::string caller_file,
			int caller_line)
{
	this->set_caller_info(caller_func, caller_file, caller_line);
	this->prep_format(mode, 2, str);
}

void	Logger::info(int fd, std::string str)
{
	this->set_header(H_I);
	this->format(fd, str);
}

void	Logger::debug(int fd, std::string str)
{
	this->set_header(H_D);
	this->format(fd, str);
}

void	Logger::warn(int fd, std::string str)
{
	this->set_header(H_W);
	this->format(fd, str);
}

void	Logger::pass	(int fd, std::string str)
{
	this->set_header(H_P);
	this->format(fd, str);
}

void	Logger::error(int fd, std::string str)
{
	this->set_header(H_E);
	this->format(fd, str);
}

