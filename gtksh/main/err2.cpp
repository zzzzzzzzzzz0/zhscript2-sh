/*
 * err2.cpp
 *
 *  Created on: 2018年5月1日
 *      Author: zzzzzzzzzzz
 */

#include "err2.h"

void err2___::throw__(const char* s1, const char* s2) {
	std::string src = "调用“/$ex/-$this-$ce-i-c*-c*”、“0”、下原样";
	if(s1) src += s1;
	if(s2) src += s2;
	src += "上原样、";
	jieshi__(src.c_str());
}
void err2___::throw2__(const char* s1, const std::exception &e) {
	throw__(s1, e.what());
}

void err2___::p__(const std::vector<std::string>& p, size_t from, size_t to, std::string& ret) {
	for(size_t i = from; i < p.size() && i <= to; i++)
		ret += p[i];
}

void err2___::buzu__(const std::vector<std::string>& p, size_t end) {
	std::string s;
	p__(p, 0, end, s);
	throw__(s.c_str(), "参数不足");
}
void err2___::buzhichi__(const std::vector<std::string>& p, size_t end) {
	std::string s;
	p__(p, 0, end, s);
	throw__(s.c_str(), "不支持");
}
void err2___::wufa__(const std::vector<std::string>& p, size_t end) {
	std::string s;
	p__(p, 0, end, s);
	throw__("无法", s.c_str());
}

err2___ err2_;
