/*
 * debug.cpp
 *
 *  Created on: 2017年10月11日
 *      Author: zzzzzzzzzzz
 */

#include "debug.h"
#include <iostream>

namespace pub {

static std::ostream &os__(char c) {
	switch(c) {
	case 'e':
		return std::cerr;
	default:
		return std::cout;
	}
}

void debug___::o2__() {
	os__(c_) << std::endl;
}
void debug___::o2__(const char *s) {
	os__(c_) << s;
}
void debug___::o2__(char *s) {
	os__(c_) << s;
}
void debug___::o2__(const std::string &s) {
	os__(c_) << s;
}
void debug___::o2__(int s) {
	os__(c_) << std::to_string(s);
}
void debug___::o2__(unsigned s) {
	os__(c_) << std::to_string(s);
}
void debug___::o2__(size_t s) {
	os__(c_) << std::to_string(s);
}
void debug___::o2__(bool s) {
	os__(c_) << (s ? "true" : "false");
}
void debug___::o2__(const std::vector<std::string>& p) {
	for(auto i : p)
		os__(c_) << i;
}

} /* namespace pub */
