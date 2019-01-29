/*
 * debug.cpp
 *
 *  Created on: 2017年10月11日
 *      Author: zzzzzzzzzzz
 */

#include "debug.h"

namespace pub {

void debug___::endl__() {
	out__() << std::endl;
}

void debug___::o2__() {
	endl__();
}
void debug___::o2__(const char *s) {
	out__() << s;
}
void debug___::o2__(char *s) {
	out__() << s;
}
void debug___::o2__(const std::string &s) {
	out__() << s;
}
void debug___::o2__(void* s) {
	out__() << s;
}
void debug___::o2__(int s) {
	out__() << std::to_string(s);
}
void debug___::o2__(unsigned s) {
	out__() << std::to_string(s);
}
void debug___::o2__(size_t s) {
	out__() << std::to_string(s);
}
void debug___::o2__(bool s) {
	out__() << (s ? "true" : "false");
}
void debug___::o2__(unsigned char s) {
	if(s >= 32 && s <= 127)
		out__() << s;
	else
		out__() << "\\x" << std::hex << (int)s << std::dec;
}
void debug___::o2__(const std::vector<std::string>& p) {
	for(auto i : p)
		out__() << i;
}

void debug___::p__(const std::vector<std::string>& p, size_t from, size_t to) {
	for(size_t i = from; i < p.size() && i <= to; i++)
		out__() << p[i];
}

} /* namespace pub */
