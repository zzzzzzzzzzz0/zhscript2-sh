/*
 * vte.cpp
 *
 *  Created on: 2017年09月12日
 *      Author: zzzzzzzzzzz
 */

#include "vte.h"
#include "view.h"
#include "pub/tag.h"
#include "pub/ext.h"

static pub::tags___ tags_ = {
		{"影子程序", "a", 0},
		{"基本环境", "e", 0},
		{"初始命令", "c", 0},
};

bool vte___::api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret) {
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y':
		switch(tag[0]) {
		case 'a': if(p.size() > 1) arg1_ = p[1]; else ret.push_back(arg1_); break;
		case 'e': if(p.size() > 1) env1_ = p[1]; else ret.push_back(env1_); break;
		case 'c': if(p.size() > 1) cmd1_ = p[1]; else ret.push_back(cmd1_); break;
		}
		return true;
	case '<':
		pub::ext_->buzu__(p, SIZE_MAX);
		return true;
	}
	return pub::plugin___::api__(shangji, p, p2, ret);
}

pub::view___* vte___::new_view__() {
	return new view___();
}

static vte___ plugin_;
extern "C" void *plugin__(const std::string &path) {return &plugin_;}
