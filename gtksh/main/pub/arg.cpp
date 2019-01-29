/*
 * arg.cpp
 *
 *  Created on: 2017年9月26日
 *      Author: zzzzzzzzzzz
 */

#include "arg.h"

namespace pub {

int args___::parse__(const std::vector<std::string>& p, size_t from) {
	arg___ *other = nullptr;
	for(auto i2 : a_) {
		if(i2.tag_.empty()) {
			other = &i2;
			break;
		}
	}
	for(size_t i = from; i < p.size();) {
		const std::string &s = p[i];
		auto fn = [&](auto i2, bool xxi) {
			if(i2->argc_ > 0) {
				if(xxi)
					++i;
				i2->i_ = i;
				i2->fn_(i2);
				i += i2->argc_ - 1;
				if(i >= p.size())
					return false;
				if(!xxi)
					i++;
			} else {
				i2->i_ = i;
				i2->fn_(i2);
			}
			return true;
		};
		bool has_tag = false;
		for(auto i2 : a_) {
			for(i2.tag_i_ = 0; i2.tag_i_ < i2.tag_.size(); i2.tag_i_++) {
				auto s2 = i2.tag_[i2.tag_i_];
				if(s2 == s) {
					if(!fn(&i2, true))
						return 1;
					has_tag = true;
					break;
				}
			}
			if(has_tag)
				break;
		}
		if(!has_tag) {
			if(!other)
				return 2;
			if(!fn(other, false))
				return 1;
			continue;
		}
		i++;
	}
	return 0;
}

} /* namespace pub */
