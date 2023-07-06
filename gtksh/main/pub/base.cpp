/*
 * base.cpp
 *
 *  Created on: 2017年12月22日
 *      Author: zzzzzzzzzzz
 */

#include "base.h"

namespace pub {

void base___::var__(const std::vector<std::string>& p, std::vector<std::string>& ret) {
	std::string name = p[1];
	if(p.size() > 2) {
		var_[name] = p[2];
	} else {
		if(var_.find(name) != var_.end())
			ret.push_back(var_[name]);
	}
}

} /* namespace pub */
