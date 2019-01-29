/*
 * util.cpp
 *
 *  Created on: 2017年11月27日
 *      Author: zzzzzzzzzzz
 */

#include "util.h"

bool util___::for_name__(const std::string& name, window___ *&w, std::string& tname) {
	std::string wname = name;
	{
		size_t i = wname.find("#");
		if(i != std::string::npos) {
			tname = wname.substr(i + 1);
			wname = wname.substr(0, i);
		}
	}
	for(auto i : windows_) {
		const char* n = i->name__();
		if(!n)
			continue;
		if(wname.empty() || n == wname) {
			w = i;
			return true;
		}
	}
	return false;
}

