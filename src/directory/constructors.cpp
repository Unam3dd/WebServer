#include "directory.hpp"
#include "logger.hpp"
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
		logz.logerr(L_WARN | L_BYPASS, "Could not open directory: " + _path);
	}
	std::sort(_files.begin(), _files.end());
}
