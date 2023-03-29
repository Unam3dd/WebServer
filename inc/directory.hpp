#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include <string>
#include <vector>

class Directory{
	public:
		Directory(const char *path);
		~Directory();
		Directory(const Directory &other);
		Directory &operator=(const Directory &other);

		inline const std::vector<std::string> &getFiles() const { return _files; }

	private:
		std::vector<std::string> _files;
		std::string				 _path;
};

#endif
