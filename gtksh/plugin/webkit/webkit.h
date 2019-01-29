/*
 * webkit.h
 *
 *  Created on: 2017年8月4日
 *      Author: zzzzzzzzzzz
 */

#ifndef WEBKIT_H_
#define WEBKIT_H_

#include "pub/plugin.h"
#include <webkit2/webkit2.h>

class webkit___: public pub::plugin___ {
public:
	webkit___();
	bool api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret);
	pub::view___* new_view__();
};

#endif /* WEBKIT_H_ */
