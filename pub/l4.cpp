/*
 * l4.cpp
 *
 *  Created on: 2019年2月13日
 *      Author: zzzzzzzzzzz
 */

#include "l4.h"
#include <dlfcn.h>

namespace pub2 {

bool dl___::load__(const char* path) {
	dl_ = dlopen(path, RTLD_LAZY);
	if(dlerr__())
		return false;
	return true;
}

bool dl___::dlerr__() {
	const char* err = dlerror();
	if(err) {
		err_ = err;
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
	get_func2__(l4_jieshi4_2__,int (*)(void*, void*, const char*,bool,const char*,void*, void*, void*));
	get_func2__(ret_push__, void (*)(void *ret, const char *s, bool one));
	get_func2__(l4_err__, const char* (*)(void*));
	get_func2__(l4_err_clear__, void (*)(void*));
	get_func2__(l4_new_var__, bool (*)(void*, void*, const char*, const char*));
	get_func2__(l4_new_def__, bool (*)(void*, void*, const char*, const char*, unsigned, unsigned, bool, bool));
	get_func2__(l4_new_alias__, bool (*)(void*, void*, const char*, const char*));
	get_func3__(new_qu__, void* (*)(void* shangji));
	get_func3__(delete_qu__, void (*)(void* qu));
	get_func3__(on_exit__, void (*)(void(*)(const char*)));
	return true;
}

bool l4___::init__(const char* path) {
	if(!dl_.load__(path))
		return false;
	if(!get_funcs__())
		return false;
	lib_ = l4_new__();
	l4_set_path__(lib_, path);
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

} /* namespace pub2 */
