/*
 * l4.h
 *
 *  Created on: 2017年8月4日
 *      Author: zzzzzzzzzzz
 */

#ifndef L4_H_
#define L4_H_

#include <string>

class dl___ {
private:
	void* dl_ = nullptr;
	bool dlerr__();

public:
	virtual ~dl___();

	bool load__(const char* path);
	void* get_func__(const char* name);
};

class l4___ {
private:
	dl___ dl_;
	bool load__(const char* path, std::string &path3);
	bool get_funcs__();

	void* lib_ = nullptr;
	void* (*l4_new__)();
	void (*l4_delete__)(void*);
	void (*l4_set_path__)(void*, const char*);
	void (*l4_cmdline_parse__)(void*, int, const char**);
	void (*l4_add_arg__)(void*, const char*);
	bool (*l4_has_src__)(void*);
	int (*l4_exit_code__)(void*);
	bool (*l4_is_end__)(void*);
	bool (*l4_jieshi3__)(void*,void*, void*);
	bool (*l4_jieshi4__)(void*, const char*,bool,const char*,void*,int,const char**, void*);
	void* (*l4_new_main_qu__)(void*);
	const char* (*l4_err__)(void*);
public:
	l4___();
	virtual ~l4___();
	bool init__(const char* line, int argc, char* argv[]);
	void uninit__();
	bool has_src__() {return l4_has_src__(lib_);}
	int exit_code__() {return l4_exit_code__(lib_);}
	bool is_end__() {return l4_is_end__(lib_);}
	int jieshi__(void* shangji, void* ret = nullptr) {return l4_jieshi3__(lib_, shangji, ret);}
	bool jieshi2__(const char* src,bool src_is_file,const char* src2,void* shangji,int argc = 0,const char**argv = nullptr, void* ret = nullptr) {
		return 	l4_jieshi4__(lib_,src,src_is_file,src2,shangji,argc,argv, ret);
	}
	void* new_main_qu__() {return l4_new_main_qu__(lib_);}
	void* (*new_qu__)(void* shangji);
	void (*delete_qu__)(void* qu);
	void (*mk_suidao__)(void *qv, const char *name, unsigned long fnaddr, bool use_a, unsigned argc, ...);
	void (*ret_push__)(void *ret, const char *s, bool one);
	const char* err__() {return l4_err__(lib_);}
};

extern bool exists__(const char *filename);

#endif /* L4_H_ */
