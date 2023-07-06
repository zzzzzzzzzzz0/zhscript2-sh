/*
 * err2.h
 *
 *  Created on: 2018年5月1日
 *      Author: zzzzzzzzzzz
 */

#ifndef ERR2_H_
#define ERR2_H_

#include <functional>
#include <vector>
#include <string>

class err2___ {
private:
	void p__(const std::vector<std::string>& p, size_t from, size_t to, std::string& ret);
public:
	std::function<bool(const char* src)> jieshi__ = nullptr;

	void throw__(const char* s1, const char* s2);
	void throw2__(const char* s1, const std::exception &e);
	void buzu__(const std::vector<std::string>& p, size_t end = SIZE_MAX);
	void buzhichi__(const std::vector<std::string>& p, size_t end = SIZE_MAX);
	void wufa__(const std::vector<std::string>& p, size_t end = SIZE_MAX);
};

extern err2___ err2_;

#endif /* ERR2_H_ */
