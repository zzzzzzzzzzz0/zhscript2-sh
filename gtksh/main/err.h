/*
 * err.h
 *
 *  Created on: 2017年8月5日
 *      Author: zzzzzzzzzzz
 */

#ifndef ERR_H_
#define ERR_H_

#include "pub/debug.h"

class err___ : public pub::debug___ {
public:
	void o31__(const char *s) {o__(s);}

	void buzu__(const std::vector<std::string>& p) {
		o__(p, "参数不足");
	}
	void buzhichi__(const std::vector<std::string>& p) {
		o__(p, "不支持");
	}
	void wufa__(const std::vector<std::string>& p) {
		o__(p, "无法");
	}

	err___(char c) {c_ = c;}
};

extern err___ err_;
extern pub::debug___ debug_;

#endif /* ERR_H_ */
