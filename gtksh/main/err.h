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
private:
	bool in_code_ = false;

	std::ostream &out__();
	void endl__();

public:
	std::string code_;

	void o31__(const char *s);

	void buzu__(const std::vector<std::string>& p, size_t end = SIZE_MAX);
	void buzhichi__(const std::vector<std::string>& p, size_t end = SIZE_MAX);
	void wufa__(const std::vector<std::string>& p, size_t end = SIZE_MAX);
};

extern err___ err_;
extern pub::debug___ debug_;

#endif /* ERR_H_ */
