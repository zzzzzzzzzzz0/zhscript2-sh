/*
 * webkit.h
 *
 *  Created on: 2017年8月4日
 *      Author: zzzzzzzzzzz
 */

#ifndef WEBKIT_H_
#define WEBKIT_H_

#include "pub/plugin.h"

class webkit___: public pub::plugin___ {
public:
	webkit___();
	bool api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret);
	pub::view___* new_view__();

#ifdef ver_world_1_
	bool zs__(guint64 page_id, const std::string& code, std::vector<std::string>& p, std::vector<std::string>& ret);
	bool allow__(const char* url);
#endif
};

#endif /* WEBKIT_H_ */
