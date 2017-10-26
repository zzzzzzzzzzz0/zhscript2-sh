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

bool exists__(const char *filename) {
	struct stat st;
	return !lstat(filename, &st);
}

bool l4___::load__(const char* path, std::string &path3) {
	std::string path2 = path;
	for(size_t i2 = 0;; i2++) {
		switch(i2) {
		case 0: case 1: {
			size_t i = path2.rfind('/');
			if(i == std::string::npos)
				continue;
			path2 = path2.substr(0, i);
			break;
		}
		case 2:
			path2 = "zhscript2";
			break;
		case 3:
			path2 = "/opt2/debug/zhscript2";
			break;
		default:
			return false;
		}
		path3 = path2 + "/l4.so";
		//debug_.o__("(", i2, ")", path3);
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
	get_func2__(l4_add_arg__, void (*)(void*, const char*));
	get_func2__(l4_has_src__, bool (*)(void*));
	get_func2__(l4_exit_code__, int (*)(void*));
	get_func2__(l4_is_end__, bool (*)(void*));
	get_func2__(l4_jieshi3__,bool (*)(void*,void*, void*));
	get_func2__(l4_new_main_qu__,void* (*)(void*));
	get_func2__(mk_suidao__, void (*)(void *qv, const char *name, unsigned long fnaddr, bool use_a, unsigned argc, ...));
	get_func2__(l4_jieshi4__,bool (*)(void*,const char*,bool,const char*,void*,int,const char**, void*));
	get_func2__(ret_push__, void (*)(void *ret, const char *s, bool one));
	get_func2__(l4_err__, const char* (*)(void*));
	get_func3__(new_qu__, void* (*)(void* shangji));
	get_func3__(delete_qu__, void (*)(void* qu));
	return true;
}

bool l4___::init__(const char* line, int argc, char* argv[]) {
	std::string path;
	if(!load__(argv[0], path)) {
		err_.o__("找不到", path);
		return false;
	}
	if(!get_funcs__())
		return false;
	lib_ = l4_new__();
	l4_set_path__(lib_, path.c_str());
	l4_add_arg__(lib_, line);
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

