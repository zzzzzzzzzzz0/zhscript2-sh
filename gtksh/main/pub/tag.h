/*
 * tag.h
 *
 *  Created on: 2017年8月5日
 *      Author: zzzzzzzzzzz
 */

#ifndef PUB_TAG_H_
#define PUB_TAG_H_

#include <string>
#include <vector>
#include <initializer_list>

namespace pub {

class tag___ {
public:
	const char *flag_, *flag2_;
	unsigned argc_;
};

class tags___ {
private:
	std::vector<tag___> a_;
public:
	tags___(std::initializer_list<tag___> a) : a_(a) {}
	char get__(const std::vector<std::string> &p, std::string &tag);
};

} /* namespace pub */

#endif /* PUB_TAG_H_ */
