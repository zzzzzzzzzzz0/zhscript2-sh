/*
 * main.h
 *
 *  Created on: 2017年8月4日
 *      Author: zzzzzzzzzzz
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "pub/plugin.h"
#include "l4.h"
#include "window.h"
#include <map>
#include <cstdarg>

class plugin_item___ {
public:
	dl___ dl_;
	pub::plugin___ *p_ = nullptr;
};

class main___: public pub::plugin___ {
private:
	void* qu_ = nullptr;
	window___ *window_ = nullptr;
	std::string code_;

	std::map<std::string, plugin_item___*> plugins_;
	bool for_plugin__(const std::string &path);

	void mk_suidao2__(void *qu);
	void mk_suidao__(void *qu, window___ *w, pub::view___ *v);
	void mk_qu__(window___*& w, pub::view___ *v, void* shangji, void*& qu);

	bool jieshi__(const char* src,const char* src2,void* shangji, bool p_has_src2, const std::vector<std::string>& p, std::vector<std::string> *ret);
	bool jieshi__(const char* src,const char* src2,void* shangji, const char* argc,va_list &argv, std::vector<std::string> *ret);
	bool jieshi__(window___* w, pub::view___ *v, const char* src, const char* src2, void* shangji, const char* argc,va_list &argv);
	bool jieshi2__(pub::view___ *v, const char* src2, const char* argc = nullptr,...);
	bool jieshi22__(void* w, const char* src2, const char* argc = nullptr,...);
	bool jieshi3__(window___* w, pub::view___ *v, const char* src, const char* src2, void* shangji, bool p_has_src2, const std::vector<std::string>& p, std::vector<std::string> *ret = nullptr);
public:
	l4___ l4_;

	main___();
	virtual ~main___();
	int main__(int argc, char* argv[]);
	void api__(window___ *window, pub::view___ *view, void* shangji, const std::vector<std::string>& p, void *ret);
	void api__(window___ *window, pub::view___ *view, void* shangji, const std::vector<std::string>& p, std::vector<std::string>& ret);
};

#endif /* MAIN_H_ */
