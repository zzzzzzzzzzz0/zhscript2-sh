/*
 * view.cpp
 *
 *  Created on: 2017年8月5日
 *      Author: zzzzzzzzzzz
 */

#include "view.h"
#include "tag.h"
#include "ext.h"
#include "util.h"
#include "eventget.h"

namespace pub {

static event_get___ event_get_;

static tags___ tags_ = {
		{"参", "p", 0},
		{"变量", "v", 1},
		{"事件", "e", 0},
};

bool view___::api__(void* shangji, const std::vector<std::string>& p, std::vector<data___>* p2, std::vector<std::string>& ret) {
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y':
		switch(tag[0]) {
		case 'p':
			if(p.size() == 1)
				ret.insert(ret.end(), init_p_.begin(), init_p_.end());
			else {
				for(size_t i = 1; i < p.size(); i++) {
					int i2 = stoi__(p[i]);
					if(i2 < 0)
						i2 += init_p_.size();
					else
						i2--;
					ret.push_back(i2 >= 0 && i2 < (int)init_p_.size() ? init_p_[i2] : "");
				}
			}
			break;
		case 'v':
			var__(p, ret);
			break;
		case 'e':
			switch(event_get_.api__(p, object__())) {
			case '<':
				ext_->buzu__(p, SIZE_MAX);
				return true;
			}
			break;
		}
		return true;
	case '<':
		ext_->buzu__(p, SIZE_MAX);
		return true;
	}
	return false;
}

void view___::add_end__(const std::vector<std::string>& p) {
	init_p_.clear();
	init_p_.insert(init_p_.end(), p.begin(), p.end());
	init_ = init2_ = false;
}

void view___::init__(const char* src2) {
	ext_->jieshi__(nullptr, this, nullptr, src2, nullptr, false, &init_p_, nullptr, nullptr);
}

void view___::init__(bool and2) {
	if(init_)
		return;
	init_ = true;
	init__("初始");
	if((and2 && var__("to")) || init2_need_)
		init2__(1);
}
void view___::init2__(int by) {
	if(!init_) {
		init2_need_ = true;
		return;
	}
	if(init2_)
		return;
	init2_ = true;
	init2_by_ = by;
	init__("初始2");
}

void view___::reinit__() {
	init_ = init2_ = false;
	init__(false);
	init2__(1);
}

} /* namespace pub */

