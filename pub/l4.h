/*
 * l4.h
 *
 *  Created on: 2019年2月13日
 *      Author: zzzzzzzzzzz
 */

#ifndef PUB2_L4_H_
#define PUB2_L4_H_

#include <string>

namespace pub2 {

class dl___ {
private:
	void* dl_ = nullptr;
	bool dlerr__();
public:
	std::string err_;

	virtual ~dl___();

	bool load__(const char* path);
	void* get_func__(const char* name);
};

class l4___ {
private:
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
	int (*l4_jieshi4_2__)(void*, void*, const char*,bool,const char*,void*, void*, void*);
	void* (*l4_new_main_qu__)(void*);
	bool (*l4_new_var__)(void*, void*, const char*, const char*);
	bool (*l4_new_def__)(void*, void*, const char*, const char*, unsigned, unsigned, bool, bool);
	bool (*l4_new_alias__)(void*, void*, const char*, const char*);
	const char* (*l4_err__)(void*);
	void (*l4_err_clear__)(void*);
protected:
	dl___ dl_;
public:
	l4___();
	virtual ~l4___();
	bool init__(const char* path);
	void uninit__();
	void parse__(int argc, const char** argv) {l4_cmdline_parse__(lib_, argc, argv);}
	void parse__(const char* s) {l4_cmdline_parse2__(lib_, s);}
	bool has_src__() {return l4_has_src__(lib_);}
	int exit_code__() {return l4_exit_code__(lib_);}
	bool is_end__() {return l4_is_end__(lib_);}
	void (*on_exit__)(void(*)(const char *name));
	int jieshi__(void* shangji, void* ret = nullptr) {return l4_jieshi3__(lib_, shangji, ret);}
	bool jieshi2__(const char* src,bool src_is_file,const char* src2,void* shangji,int argc = 0,const char**argv = nullptr, void* ret = nullptr) {
		return l4_jieshi4__(lib_,src,src_is_file,src2,shangji,argc,argv, ret);
	}
	int jieshi3__(const char* src,bool src_is_file,const char* src2,void* shangji, void* ce = nullptr, void* args = nullptr, void* ret = nullptr) {
		return l4_jieshi4_2__(lib_, ce, src,src_is_file,src2,shangji, args, ret);
	}
	void* new_main_qu__() {return l4_new_main_qu__(lib_);}
	void* (*new_qu__)(void* shangji);
	void (*delete_qu__)(void* qu);
	bool new_var__(void *qu, const char* name, const char* val) {
		return l4_new_var__(lib_, qu, name, val);
	}
	bool new_def__(void* qu, const char* name, const char* val, unsigned argc, unsigned back_arg, bool is_priv, bool is_through) {
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

} /* namespace pub2 */

#endif /* PUB2_L4_H_ */
