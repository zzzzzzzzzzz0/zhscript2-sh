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
#include <functional>

namespace pub {

class arg___ {
public:
	std::function<void(arg___*)> fn_;
	std::vector<std::string> tag_;
	int argc_ = 0;
	size_t i_, tag_i_;
};

class args___ {
public:
	std::vector<arg___> a_;
	args___(std::initializer_list<arg___> a) : a_(a) {}
	int parse__(const std::vector<std::string>& p, size_t from = 0);
};

} /* namespace pub */

#endif /* PUB_ARG_H_ */
