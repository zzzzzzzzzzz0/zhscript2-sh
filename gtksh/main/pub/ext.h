/*
 * ext.h
 *
 *  Created on: 2017年8月7日
 *      Author: zzzzzzzzzzz
 */

#ifndef PUB_EXT_H_
#define PUB_EXT_H_

#include "view.h"
#include "addopt.h"
#include "plugin.h"
#include <functional>

namespace pub {

#define null_ "NULL"

class ext___ {
public:
	/*template<typename... T> using o___ = void (T...);
	o___ *o__ = nullptr;*/
	std::function<void(const char*)> err__ = nullptr;
	std::function<void(const std::vector<std::string>& p, size_t)> buzu__ = nullptr;
	std::function<void(const std::vector<std::string>& p, size_t)> buzhichi__ = nullptr;
	std::function<void(const std::vector<std::string>& p, size_t)> wufa__ = nullptr;
	std::function<void(const char* s1, const char* s2)> throw__ = nullptr;
	std::function<void(const char* s1, const std::exception &e)> throw2__ = nullptr;
	std::function<void(const std::vector<std::string>& p, size_t)> throw_buzu__ = nullptr;
	std::function<void(const std::vector<std::string>& p, size_t)> throw_buzhichi__ = nullptr;
	std::function<void(const std::vector<std::string>& p, size_t)> throw_wufa__ = nullptr;

	std::function<bool (void* w, view___ *v, const char* src, const char* src2, void* shangji, bool p_has_src2, std::vector<std::string>* p, std::vector<pub::data___>* p2, std::vector<std::string> *ret)> jieshi__ = nullptr;
	bool jieshi2__(pub::view___ *v, const char* src2, const char* argc = nullptr,...);
	bool jieshi21__(void* w, const char* src2, const char* argc = nullptr,...);
	bool jieshi22__(void* user_data, const char* argc = nullptr,...);
	bool jieshi23__(const char* src, const char* src2 = nullptr, void* shangji = nullptr, const char* argc = nullptr,...);

	bool (*add_begin__)(view___ *, void* w, view___ *, add_opt___*) = nullptr;
	std::function<void(void* w, pub::view___ *v, std::vector<std::string>& p3, pub::add_opt___& opt)> jieshi_b__ = nullptr;
	void (*add_end__)(view___ *, void* w, add_opt___*, std::vector<std::string>*, plugin___*) = nullptr;
	void (*close__)(view___ *) = nullptr;
	view___ *(*view__)(void *) = nullptr;
	view___* (*get_view__)(const std::string& name1, unsigned long id2) = nullptr;
	void (*push__)(view___*, const char*, std::vector<std::string>&) = nullptr;
	bool (*wait__)(const char* s) = nullptr;
};

extern ext___* ext_;

} /* namespace pub */

#endif /* PUB_EXT_H_ */
