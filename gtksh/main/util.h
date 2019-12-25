/*
 * util.h
 *
 *  Created on: 2017年11月27日
 *      Author: zzzzzzzzzzz
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "window.h"
#include "area.h"

class util___ {
public:
	static bool for_name__(const std::string& name, window___ *&w, std::string& tname);
	static pub::view___* get_view__(const std::string& name1, unsigned long id2);
};

#endif /* UTIL_H_ */
