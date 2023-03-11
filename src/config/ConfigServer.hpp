#ifndef CONFIGSERVER_HPP
# define CONFIGSERVER_HPP
# include "file.hpp"
# include <string>

class ConfigServer: public File{
	public:
		ConfigServer();
		ConfigServer(const std::string &filename);
		ConfigServer(const ConfigServer &rhs);
		~ConfigServer();

	private:
		ConfigServer &operator=(const ConfigServer &rhs);
		
};

#endif
