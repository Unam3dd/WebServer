#include "directory.hpp"
#include "http_colors.hpp"
#include <algorithm>
#include <dirent.h>
#include <iostream>

Directory::Directory(const char *path): _path(path){
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(path)) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			_files.push_back(ent->d_name);
		}
		closedir(dir);
	} else {
		std::cerr << WARN << "Could not open directory: " << path << std::endl;
	}
	std::sort(_files.begin(), _files.end());
}
