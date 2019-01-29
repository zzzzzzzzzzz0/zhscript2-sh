/*
 * err.cpp
 *
 *  Created on: 2017年8月5日
 *      Author: zzzzzzzzzzz
 */

#include "err.h"
#include <sstream>
#include "pub/ext.h"

static std::stringstream ss_;

void err___::endl__() {
	const std::string &s = ss_.str();
	ss_.str("");
	std::cerr << s << std::endl;
	if(!code_.empty() && !in_code_) {
		in_code_ = true;
		pub::ext_->jieshi23__(code_.c_str(), nullptr, nullptr, "s", s.c_str());
		in_code_ = false;
	}
}

std::ostream& err___::out__() {
	return ss_;
}

void err___::o31__(const char *s) {
	o__(s);
}

void err___::buzu__(const std::vector<std::string>& p, size_t end) {
	p__(p, 0, end);
	o__("参数不足");
}
void err___::buzhichi__(const std::vector<std::string>& p, size_t end) {
	p__(p, 0, end);
	o__("不支持");
}
void err___::wufa__(const std::vector<std::string>& p, size_t end) {
	o2__("无法");
	p__(p, 0, end);
	o2__();
}

err___ err_;
pub::debug___ debug_;
