/*
 * util.h
 *
 *  Created on: 2017年12月22日
 *      Author: zzzzzzzzzzz
 */

#ifndef PUB_UTIL_H_
#define PUB_UTIL_H_

#include <string>
#include <vector>

namespace pub {

int stoi__(const std::string& s, int i0);
int stoi__(const std::string& s);
unsigned long stoul__(const std::string& s);
bool bool__(const std::string& s);
bool bool__(const std::vector<std::string>& p, size_t i, bool b = false);

void cerr__(const std::string& s, const std::exception& e);

} /* namespace pub */

#endif /* PUB_UTIL_H_ */
