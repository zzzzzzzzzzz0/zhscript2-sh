/*
 * debug.h
 *
 *  Created on: 2017年10月11日
 *      Author: zzzzzzzzzzz
 */

#ifndef PUB_DEBUG_H_
#define PUB_DEBUG_H_

#include <string>
#include <vector>
#include <iostream>

namespace pub {

class debug___ {
private:
	template<typename T, typename... T2>
	void o2__(T t2, T2... t) {
		o2__(t2);
		o2__(t...);
	}
protected:
	virtual std::ostream &out__() {
		return std::cout;
	}
	virtual void endl__();

	void o2__();
	void o2__(const char *s);
	void o2__(char *s);
	void o2__(const std::string &s);
	void o2__(int s);
	void o2__(unsigned s);
	void o2__(size_t s);
	void o2__(bool s);
	void o2__(unsigned char s);
	void o2__(char s) {o2__((unsigned char)s);}
	void o2__(void* s);
	void o2__(const std::vector<std::string>& p);

	void p__(const std::vector<std::string>& p, size_t from, size_t to);
public:
	virtual ~debug___() {};

	template<typename... T>
	void o__(T... t) {
		o2__(t...);
		o2__();
	}
};

} /* namespace pub */

#endif /* PUB_DEBUG_H_ */
