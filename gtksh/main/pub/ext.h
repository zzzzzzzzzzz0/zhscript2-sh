/*
 * ext.h
 *
 *  Created on: 2017年8月7日
 *      Author: zzzzzzzzzzz
 */

#ifndef PUB_EXT_H_
#define PUB_EXT_H_

#include "view.h"
#include <functional>

namespace pub {

class ext___ {
public:
	/*template<typename... T> using o___ = void (T...);
	o___ *o__ = nullptr;*/
	std::function<void(const char*)> err__ = nullptr;
	std::function<void(const std::vector<std::string>& p)> buzu__ = nullptr;
	std::function<void(const std::vector<std::string>& p)> buzhichi__ = nullptr;

	std::function<bool (view___ *v, const char* src, void* shangji, bool p_has_src2, const std::vector<std::string>& p, std::vector<std::string> *ret)> jieshi__ = nullptr;
	std::function<bool (view___ *, const char*)> jieshi2__ = nullptr;
	std::function<bool (view___ *, const char*, const char*)> jieshi2s__ = nullptr;
	std::function<bool (view___ *, const char*, const char*, const char*)> jieshi2ss__ = nullptr;
	std::function<bool (view___ *, const char*, const char*, const char*, const char*)> jieshi2sss__ = nullptr;
	std::function<bool (void *, const char*)> jieshi3__ = nullptr;

	void(* add_begin__)(view___ *, void* w, bool from_view) = nullptr;
	void(* add_end__)(view___ *, bool) = nullptr;
	void(* close__)(view___ *) = nullptr;
};

extern ext___* ext_;

} /* namespace pub */

#endif /* PUB_EXT_H_ */
