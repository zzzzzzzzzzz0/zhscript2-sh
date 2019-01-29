/*
 * l4.cpp
 *
 *  Created on: 2017年8月4日
 *      Author: zzzzzzzzzzz
 */

#include "l4.h"

#include "l4.h"
#include <dlfcn.h>
#include <sys/stat.h>
#include "err.h"
#include <unistd.h>

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

bool l4___::load__(const char* path, std::string &path3, std::string &path1, std::string &path11) {
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
		for(;realpath__(path2););
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
	return dl_.load__(path3.c_str());
}

bool dl___::load__(const char* path) {
	dl_ = dlopen(path, RTLD_LAZY);
	if(dlerr__())
		return false;
	return true;
}

bool dl___::dlerr__() {
	const char *err = dlerror();
	if(err) {
		err_.o__(err);
		return true;
	}
	return false;
}

void* dl___::get_func__(const char* name) {
	void* v = dlsym(dl_, name);
	return dlerr__() ? nullptr : v;
}
#define get_func2__(n,p)	\
	if(!(n = (p)dl_.get_func__(#n)))	\
		return false;
#define get_func3__(n,p)	\
	if(!(n = (p)dl_.get_func__("l4_" # n)))	\
		return false;
bool l4___::get_funcs__() {
	get_func2__(l4_new__,void*(*)());
	get_func2__(l4_delete__,void(*)(void*));
	get_func2__(l4_set_path__,void (*)(void*,const char*));
	get_func2__(l4_cmdline_parse__, void(*)(void*, int, const char**));
	get_func2__(l4_cmdline_parse2__, void (*)(void*, const char*));
	get_func2__(l4_has_src__, bool (*)(void*));
	get_func2__(l4_exit_code__, int (*)(void*));
	get_func2__(l4_is_end__, bool (*)(void*));
	get_func2__(l4_jieshi3__,bool (*)(void*,void*, void*));
	get_func2__(l4_new_main_qu__,void* (*)(void*));
	get_func2__(mk_suidao__, void (*)(void *qv, const char *name, unsigned long fnaddr, bool use_a, unsigned argc, ...));
	get_func2__(l4_jieshi4__,bool (*)(void*,const char*,bool,const char*,void*,int,const char**, void*));
	get_func2__(ret_push__, void (*)(void *ret, const char *s, bool one));
	get_func2__(l4_err__, const char* (*)(void*));
	get_func2__(l4_err_clear__, void (*)(void*));
	get_func2__(l4_new_var__, bool (*)(void*, void*, const char*, const char*));
	get_func2__(l4_new_def__, bool (*)(void*, void*, const char*, const char*, size_t, size_t, bool, bool));
	get_func2__(l4_new_alias__, bool (*)(void*, void*, const char*, const char*));
	get_func3__(new_qu__, void* (*)(void* shangji));
	get_func3__(delete_qu__, void (*)(void* qu));
	get_func3__(on_exit__, void (*)(void(*)(const char*)));
	return true;
}

bool l4___::init__(const char* line1, int argc, char* argv[], std::string &path1) {
	std::string path, path2 = path1;
	if(!load__(argv[0], path, path1, path2)) {
		err_.o__("找不到", path);
		return false;
	}
	if(!get_funcs__())
		return false;
	lib_ = l4_new__();
	l4_set_path__(lib_, path.c_str());
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
	l4_cmdline_parse2__(lib_, line.c_str());
	l4_cmdline_parse__(lib_, argc, (const char**)argv);
	return true;
}
void l4___::uninit__() {
	if(lib_) {
		l4_delete__(lib_);
		lib_ = nullptr;
	}
}

dl___::~dl___() {
	if(dl_) {
		dlclose(dl_);
		dl_ = nullptr;
	}
}

l4___::l4___() {
}

l4___::~l4___() {
	uninit__();
}

