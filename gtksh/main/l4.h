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
	bool load__(const char* path, std::string &path3, std::string &path1, std::string &path11);
	bool get_funcs__();

	void* lib_ = nullptr;
	void* (*l4_new__)();
	void (*l4_delete__)(void*);
	void (*l4_set_path__)(void*, const char*);
	void (*l4_cmdline_parse__)(void*, int, const char**);
	void (*l4_cmdline_parse2__)(void*, const char*);
	bool (*l4_has_src__)(void*);
	int (*l4_exit_code__)(void*);
	bool (*l4_is_end__)(void*);
	bool (*l4_jieshi3__)(void*,void*, void*);
	bool (*l4_jieshi4__)(void*, const char*,bool,const char*,void*,int,const char**, void*);
	void* (*l4_new_main_qu__)(void*);
	bool (*l4_new_var__)(void*, void*, const char*, const char*);
	bool (*l4_new_def__)(void*, void*, const char*, const char*, size_t, size_t, bool, bool);
	bool (*l4_new_alias__)(void*, void*, const char*, const char*);
	const char* (*l4_err__)(void*);
	void (*l4_err_clear__)(void*);
public:
	l4___();
	virtual ~l4___();
	bool init__(const char* line, int argc, char* argv[], std::string &path);
	void uninit__();
	bool has_src__() {return l4_has_src__(lib_);}
	int exit_code__() {return l4_exit_code__(lib_);}
	bool is_end__() {return l4_is_end__(lib_);}
	void (*on_exit__)(void(*)(const char *name));
	int jieshi__(void* shangji, void* ret = nullptr) {return l4_jieshi3__(lib_, shangji, ret);}
	bool jieshi2__(const char* src,bool src_is_file,const char* src2,void* shangji,int argc = 0,const char**argv = nullptr, void* ret = nullptr) {
		return l4_jieshi4__(lib_,src,src_is_file,src2,shangji,argc,argv, ret);
	}
	void* new_main_qu__() {return l4_new_main_qu__(lib_);}
	void* (*new_qu__)(void* shangji);
	void (*delete_qu__)(void* qu);
	bool new_var__(void *qu, const char* name, const char* val) {
		return l4_new_var__(lib_, qu, name, val);
	}
	bool new_def__(void* qu, const char* name, const char* val, size_t argc, size_t back_arg, bool is_priv, bool is_through) {
		return l4_new_def__(lib_, qu, name, val, argc, back_arg, is_priv, is_through);
	}
	bool new_alias__(void* qu, const char* name, const char* val) {
		return l4_new_alias__(lib_, qu, name, val);
	}
	void (*mk_suidao__)(void *qv, const char *name, unsigned long fnaddr, bool use_a, unsigned argc, ...);
	void (*ret_push__)(void *ret, const char *s, bool one);
	const char* err__() {return l4_err__(lib_);}
	void err_clear__() {l4_err_clear__(lib_);}
};

extern bool exists__(const char *filename);
extern bool is_symlink__(const char *filename);
extern bool realpath__(std::string &path);
extern bool realpath2__(std::string &path);

#endif /* L4_H_ */
