/*
 * l4.cpp
 *
 *  Created on: 2017年8月4日
 *      Author: zzzzzzzzzzz
 */

#include "l4.h"
#include <sys/stat.h>
#include <unistd.h>
#include "err.h"

bool exists__(const char *filename) {
	struct stat st;
	return !lstat(filename, &st);
}
bool is_symlink__(const char *filename) {
	struct stat buf;
	return lstat(filename, &buf) == 0 && S_ISLNK(buf.st_mode);
}
bool realpath__(std::string &path) {
	char buf[512] = "";
	readlink(path.c_str(), buf,512);
	if(!buf[0])
		return false;
	if(buf[0] == '/')
		path = buf;
	else {
		size_t i = path.rfind('/');
		path = path.substr(0, i + 1) + buf;
	}
	return true;
}
bool realpath2__(std::string &path) {
	char* env = std::getenv("PATH");
	if(env) {
		std::string env2 = env;
		for(size_t i = 0, i2; i < env2.size();) {
			i2 = env2.find(':', i);
			if(i2 == std::string::npos)
				i2 = env2.size();
			if(i < i2) {
				std::string path2 = env2.substr(i, i2 - i) + "/" + path;
				if(exists__(path2.c_str())) {
					path = path2;
					return true;
				}
			}
			i = i2 + 1;
		}
	}
	return false;
}

bool l4___::path__(const char* path, std::string &path3, std::string &path1, std::string &path11, std::string &path12) {
	std::string path2 = path;
	if(path2.rfind('/') == std::string::npos) {
		if(realpath2__(path2)) {
			if(is_symlink__(path2.c_str())) {
				realpath__(path2);
				path11 = path2;
			}
		}
	}
	if(is_symlink__(path2.c_str())) {
		for(;realpath__(path2);) {
			if(path12.empty())
				path12 = path2;
		}
	}
	path1 = path2;
	for(size_t i2 = 0;; i2++) {
		//debug_.o__("(", i2, ")", path2);
		switch(i2) {
		case 0: case 1: case 3: case 4: {
			size_t i = path2.rfind('/');
			if(i == std::string::npos)
				continue;
			path2 = path2.substr(0, i);
			break;
		}
		case 2:
			if(is_symlink__(path)) {
				path2 = path;
				for(; realpath__(path2););
				path1 = path2;
				continue;
			}
		default:
			return false;
		}
		path3 = path2 + "/l4.so";
		//debug_.o__(path3);
		if(exists__(path3.c_str()))
			break;
	}
	return true;
}

bool l4___::init2__(const char* line1, int argc, char* argv[], std::string &path1, std::string &path12) {
	std::string path2 = path1;
	if(!path__(argv[0], path_, path1, path2, path12)) {
		err_.o__("找不到", path_);
		return false;
	}
	if(!init__(path_.c_str())) {
		err_.o__(dl_.err_);
		return false;
	}
	std::string line = line1;
	bool ex = false;
	for(;;) {
		std::string path3 = path2;
		auto fn = [&]() {
			path2 = path3 + ".zs";
			return (ex = exists__(path2.c_str()));
		};
		if(fn()) break;
		std::string zs = "_zs";
		size_t i = path3.length() > zs.length() ? path3.length() - zs.length() : 0;
		if(path3.rfind(zs) == i) {
			path3 = path3.substr(0, i);
			if(fn()) break;
		}
		zs = "zs_";
		size_t i2 = path3.rfind("/") + 1;
		if(path3.find(zs, i2) == i2) {
			path3 = path3.substr(0, i2) + path3.substr(i2 + zs.length());
			if(fn()) break;
		}
		break;
	}
	if(ex) {
		line += " \"" + path2 + "\"";
	}
	//debug_.o__(line);
	parse__(line.c_str());
	parse__(argc, (const char**)argv);
	return true;
}

l4___::l4___() {
}

l4___::~l4___() {
}

