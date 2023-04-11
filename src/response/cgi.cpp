#include "http_response.hpp"
#include <cstdlib>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <iostream>
#include <sys/stat.h>

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

int	HttpResponse::_processCgi(const std::string& path, const std::string& file)
{
	std::string	command;
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
	
	close(fd[0]);

	return (0);
}