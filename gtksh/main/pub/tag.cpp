/*
 * tag.cpp
 *
 *  Created on: 2017年8月5日
 *      Author: zzzzzzzzzzz
 */

#include "tag.h"

namespace pub {

char tags___::get__(const std::vector<std::string>& p, std::string &tag) {
	if(p.size() == 0)
		return '<';
	for(tag___ i : a_) {
		if(p[0] == i.flag_) {
			if(p.size() >= i.argc_ + 1) {
				tag = i.flag2_;
				return 'y';
			}
			return '<';
		}
	}
	return 'n';
}

} /* namespace pub */
