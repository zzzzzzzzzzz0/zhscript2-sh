/*
 * arg.h
 *
 *  Created on: 2017年9月26日
 *      Author: zzzzzzzzzzz
 */

#ifndef PUB_ARG_H_
#define PUB_ARG_H_

#include <string>
#include <vector>
#include <initializer_list>

namespace pub {

class arg___ {
public:
	const char *tag_ = nullptr;
	int argc_ = 1;
	std::vector<std::string> a_;
};

class args___ {
private:
	std::vector<arg___*> a_;
public:
	args___(std::initializer_list<arg___*> a) : a_(a) {}
	bool parse__(const std::vector<std::string>& p, size_t from = 0);
};

} /* namespace pub */

#endif /* PUB_ARG_H_ */
