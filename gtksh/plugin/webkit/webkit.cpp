/*
 * webkit.cpp
 *
 *  Created on: 2017年8月4日
 *      Author: zzzzzzzzzzz
 */

#include "webkit.h"
#include "view.h"

pub::view___* webkit___::new_view__() {
	return new view___();
}

static webkit___ plugin_;
extern "C" void *plugin__(const std::string &path) {
	std::string dir = path.substr(0, path.rfind('/'));
	//g_message("%s", dir.c_str());
	webkit_web_context_set_web_extensions_directory(webkit_web_context_get_default(), dir.c_str());
	return &plugin_;
}
