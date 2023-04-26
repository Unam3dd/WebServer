#include "http_response.hpp"
#include "http_colors.hpp"
#include "http_utils.hpp"
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

void	HttpResponse::_createCgiArgv(const std::string& path, const std::string& file){
	static std::vector <char*> argv;
	argv.clear();

	argv.push_back(const_cast<char*>(path.c_str()));
	argv.push_back(const_cast<char*>(file.c_str()));
	argv.push_back(NULL);
	this->_cgiargv = argv;

}

void HttpResponse::_createCgiEnvp(const std::string& file){

	static std::vector<std::string> env;
	env.clear();
	char **origenvp = SG_ENVP(NULL);
	for (int i = 0; origenvp[i]; i++)
		env.push_back(origenvp[i]);

	std::vector<char*> envp;

	std::string	command;
	std::string	pathtranslated;

	// Serv Variables
	std::string redirect = "REDIRECT_STATUS=301";
	std::string software = "SERVER_SOFTWARE=" + std::string("WebServ/") + std::string(VERSION);
	std::string interface = "GATEWAY_INTERFACE=CGI/1.1";
	std::string host = "SERVER_NAME=" + this->_request.getHeaders().at("host");
	env.push_back(redirect);
	env.push_back(software);
	env.push_back(interface);
	env.push_back(host);

	// Req Variables
	std::string scriptname = "SCRIPT_NAME=" + this->_request.getUri();
	std::string protocol = "SERVER_PROTOCOL=" + this->getVersion();
	std::string port = "SERVER_PORT=" + NumberToString(this->_request.getPort());
	std::string method = "REQUEST_METHOD=" + std::string(STR_METHOD(this->_request.getMethod()));
	pathtranslated = "PATH_TRANSLATED=" + file;
	env.push_back(protocol);
	env.push_back(port);
	env.push_back(method);
	env.push_back(pathtranslated);

	std::string query = "QUERY_STRING=" + this->_request.getQueryString();
	std::string remoteaddr = "REMOTE_ADDR=" + this->_request.getIp();
	env.push_back(query);
	env.push_back(remoteaddr);
	
	std::string cookies;
	if (   ( this->_reqcfg && this->_reqcfg->GetCookies()) 
		|| ( this->_srvcfg && this->_srvcfg->GetCookies()) )
		cookies = "HTTP_COOKIE=" + this->_request.getHeaders().at("cookie");
	else
		cookies = "HTTP_COOKIE=";

	std::string accept = "HTTP_ACCEPT=" + this->_request.getHeaders().at("accept");
	std::string acceptlang = "HTTP_ACCEPT_LANGUAGE=" + this->_request.getHeaders().at("accept-language");
	std::string acceptenc = "HTTP_ACCEPT_ENCODING=" + this->_request.getHeaders().at("accept-encoding");
	std::string useragent = "HTTP_USER_AGENT=" + this->_request.getHeaders().at("user-agent");
	std::string referer = "HTTP_REFERER=" + this->_request.getHeaders().at("referer");
	std::string contenttype = "CONTENT_TYPE=" + this->_request.getHeaders().at("content-type");
	
	std::string contentlen;
	this->_request.getMethod() == POST ? contentlen = "CONTENT_LENGTH=" + NumberToString(this->_request.getBody().size()) 
									   : contentlen = "CONTENT_LENGTH=0";
	
	env.push_back(cookies);
	env.push_back(accept);
	env.push_back(acceptlang);
	env.push_back(acceptenc);
	env.push_back(useragent);
	env.push_back(referer);
	env.push_back(contenttype);
	env.push_back(contentlen);
	
	envp.reserve(env.size() + 1);

	for (size_t i = 0; i < env.size(); i++)
		envp.push_back(const_cast<char*>(env[i].data()));

	envp.push_back(NULL);
	this->_cgienvp = envp;
}

int	HttpResponse::_processCgi(const std::string& path, const std::string& file)
{
	std::string	command = "";
	int	len = 0, capacity = 0;
	int	inputfd[2] = {0, 0};
	int	outputfd[2] = {0, 0};

	if (path.empty() || file.empty()) return (1);

	if (!is_valid_cgi(path))
		return (1);

	_cgibuf.clear();
	command = path + " " + file;
	
	if (DEBUG)
	{
		std::cout << DBG << "[HttpResponse::_processCgi] Processing File: " << file << std::endl;
		std::cout << DBG << "[HttpResponse::_processCgi] Cgi Path: " << path << std::endl;
	}

	if (pipe(inputfd) < 0 || pipe(outputfd) < 0)
	{
		if (DEBUG)
			std::cout << DBG << FAIL << "[HttpResponse::_processCgi] Pipe Error" << std::endl;
		return (1);
	}
	

	if (!fork()) {
		close(inputfd[1]);
		close(outputfd[0]);
		dup2(inputfd[0], STDIN_FILENO);
		dup2(outputfd[1], STDOUT_FILENO);
		_createCgiArgv(path, file);
		_createCgiEnvp(file);
		execve(path.c_str(), &this->_cgiargv[0], &this->_cgienvp[0]);
		exit(1);
	}
	close(inputfd[0]);
	close(outputfd[1]);

	if (this->_request.getMethod() == POST)
	{
		if (DEBUG)
			std::cout << DBG << "[HttpResponse::_processCgi] POST Request" << std::endl;
		if (write(inputfd[1], this->_request.getBody().c_str(), this->_request.getBody().size()) < 0)
		{
			if (DEBUG)
				std::cout << DBG << FAIL << "[HttpResponse::_processCgi] Write Error" << std::endl;
			return (1);
		}
	}
	bool datainbuffer = true;
	while (datainbuffer)
	{
		char buf[1024];
		int ret = read(outputfd[0], buf, 1024);
		if (ret > 0)
		{
			if (len + ret > capacity)
			{
				capacity = len + ret + 1;
				_cgibuf.resize(capacity);
			}
			memcpy(&_cgibuf[len], buf, ret);
			len += ret;
		}
		else
			datainbuffer = false;
	}
	wait(NULL);

	if (DEBUG)
	{
		if (len < 10000)
			std::cout << DBG << "[HttpResponse::_processCgi] Cgi Output: " << _cgibuf.data() << std::endl;
		else
			std::cout << DBG << "[HttpResponse::_processCgi] Cgi Output not displayed due to big size (>10000 chars)"  << std::endl;
	}

	close(inputfd[1]);
	close(outputfd[0]);

	return (0);
}
