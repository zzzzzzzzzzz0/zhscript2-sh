/*
 * arg.cpp
 *
 *  Created on: 2017年9月26日
 *      Author: zzzzzzzzzzz
 */

#include "arg.h"

namespace pub {

bool args___::parse__(const std::vector<std::string>& p, size_t from) {
	if(a_.size() == 0)
		return false;
	arg___ *other = nullptr;
	for(auto i2 : a_) {
		if(!i2->tag_) {
			other = i2;
			break;
		}
	}
	for(auto i = p.begin() += from; i != p.end();) {
		const std::string &s = *i;
		bool has_tag = false;
		for(auto i2 : a_) {
			if(!i2->tag_)
				continue;
			if(s == i2->tag_) {
				switch(i2->argc_) {
				case -1:
					i2->a_.push_back("1");
					break;
				case 0:
					i2->a_.push_back("");
					break;
				default:
					for(int i3 = 0; i3 < i2->argc_; i3++) {
						if(++i == p.end())
							return false;
						i2->a_.push_back(*i);
					}
					break;
				}
				has_tag = true;
				break;
			}
		}
		if(!has_tag) {
			if(!other)
				return false;
			for(int i3 = 0; i3 < other->argc_; i3++, i++) {
				if(i == p.end())
					return false;
				other->a_.push_back(*i);
			}
			continue;
		}
		i++;
	}
	return true;
}

} /* namespace pub */
