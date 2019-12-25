/*
 * main.h
 *
 *  Created on: 2017年8月4日
 *      Author: zzzzzzzzzzz
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "pub/plugin.h"
#include "pub/addopt.h"
#include "l4.h"
#include "window.h"
#include <map>

class plugin_item___ {
public:
	pub2::dl___ dl_;
	pub::plugin___ *p_ = nullptr;
};

class main___: public pub::plugin___ {
private:
	void* qu_ = nullptr;
	std::string code_;

	std::map<std::string, plugin_item___*> plugins_;
	bool for_plugin__(const std::string &path);

	void mk_suidao__(void *qu, window___ *w, pub::view___ *v, std::vector<pub::data___>* p2);
	void mk_qu__(window___*& w, pub::view___ *v, std::vector<pub::data___>* p2, void* shangji, void*& qu);

	bool jieshi__(const char* src,const char* src2,void* shangji, bool p_has_src2, std::vector<std::string>* p, std::vector<std::string> *ret);
	bool jieshi3__(void* w, pub::view___ *v, const char* src, const char* src2, void* shangji, bool p_has_src2, std::vector<std::string>* p, std::vector<pub::data___>* p2, std::vector<std::string> *ret = nullptr);
	void jieshi_b__(void* w, pub::view___ *v, std::vector<std::string>& p3, pub::add_opt___& opt);

	void static__();
public:
	l4___ l4_;
	window___ *window_ = nullptr;
	bool loops_ = false;

	main___();
	virtual ~main___();
	int main__(int argc, char* argv[]);
	void api__(window___ *window, pub::view___ *view, void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, void *ret);
	void api__(window___ *window, pub::view___ *view, void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret);
};

#endif /* MAIN_H_ */
