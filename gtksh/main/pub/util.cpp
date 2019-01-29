/*
 * util.cpp
 *
 *  Created on: 2017年12月22日
 *      Author: zzzzzzzzzzz
 */

#include "util.h"
#include <iostream>

namespace pub {

bool bool__(const std::string& val) {
	return !(val.empty() || val == "0" || val == "false" || val == "NULL");
}
bool bool__(const std::vector<std::string>& p, size_t i, bool b) {
	return p.size() > i ? bool__(p[i]) : b;
}

int stoi__(const std::string& s, int i0) {
	if(s.empty())
		return i0;
	int i;
	switch(s[0]) {
	case '+':
		i = stoi__(s.substr(1));
		i += i0;
		break;
	default:
		i = stoi__(s);
		break;
	}
	return i;
}

int stoi__(const std::string& s) {
	try {return std::stoi(s);} catch(std::exception& e) {cerr__(s, e); return 0;}
}
unsigned long stoul__(const std::string& s) {
	try {return std::stoul(s);} catch(std::exception& e) {cerr__(s, e); return 0;}
}

void cerr__(const std::string& s, const std::exception& e) {
	std::cerr << e.what() << " " << s << std::endl;
}

} /* namespace pub */
