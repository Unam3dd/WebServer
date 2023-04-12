#include "http_response.hpp"
#include <cstdlib>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <iostream>
#include <sys/stat.h>
#include <cstring>

static bool	is_valid_cgi(const std::string& path)
{
	struct stat	s;

	if (path.empty())
		return (false);

	if (stat(path.c_str(), &s) < 0)
		return (false);
	if (S_ISDIR(s.st_mode))
		return (false);
	if (!(s.st_mode & S_IXUSR))
		return (false);
	return (true);
}

void HttpResponse::_populateCgiEnv(void){

	std::string	command;
	std::string	pathtranslated;

	// Serv Variables
	std::string software = "WebServ/" + std::string(VERSION);
	std::string interface = "CGI/1.1";
	std::string host = this->_request.getHeaders().at("host");

	// Req Variables
	std::string protocol = this->getVersion();
	std::string port = NumberToString(this->_request.getPort());
	std::string method = STR_METHOD(this->_request.getMethod());
	std::string path = "";
	if (_reqcfg && _reqcfg->GetRoot() != "")
		pathtranslated = this->_reqcfg->GetRoot() + this->_request.getUri();
	else
		pathtranslated = this->_srvcfg->GetRoot() + this->_request.getUri();

	std::string query = _getQuery();
	std::string remoteaddr = this->_request.getIp();

	command = "export SERVER_SOFTWARE=" + software; 
	std::system(command.c_str());
	command = "export SERVER_NAME=" + host; 
	std::system(command.c_str());
	command = "export GATEWAY_INTERFACE=" + interface; 
	std::system(command.c_str());
	command = "export SERVER_PROTOCOL=" + protocol; 
	std::system(command.c_str());
	command = "export SERVER_PORT=" + port; 
	std::system(command.c_str());
	command = "export REQUEST_METHOD=" + method; 
	std::system(command.c_str());
	command = "export PATH_INFO=" + path; 
	std::system(command.c_str());
	command = "export PATH_TRANSLATED=" + pathtranslated; 
	std::system(command.c_str());
	command = "export QUERY_STRING=" + query; 
	std::system(command.c_str());
}

int	HttpResponse::_processCgi(const std::string& path, const std::string& file)
{
	std::string	command = "";
	int			len = 0, capacity = 0;
	int	fd[2] = {0, 0};

	if (path.empty() || file.empty()) return (1);

	if (!is_valid_cgi(path))
		return (1);

	_cgibuf.clear();
	command = path + " " + file;

	if (pipe(fd) < 0)
		return (1);

	if (!fork()) {
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		_populateCgiEnv();
		std::system(command.c_str());
		exit(1);
	}
	close(fd[1]);

	wait(NULL);

	ioctl(fd[0], FIONREAD, &len);

	capacity = _cgibuf.capacity();
	
	if (len > capacity)
		_cgibuf.reserve(len+1);

	if (::read(fd[0], const_cast<char*>(_cgibuf.c_str()), len) != (int)len)
		return (1);

	std::cout << "TA GRAND MERE EN SLIP " << _cgibuf.data() << std::endl;

	_cgibuf.resize(std::strlen(_cgibuf.data()));

	std::cout << _cgibuf.size() << std::endl;
	
	close(fd[0]);

	return (0);
}
