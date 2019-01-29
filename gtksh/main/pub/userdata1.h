/*
 * userdata1.h
 *
 *  Created on: 2017年12月22日
 *      Author: zzzzzzzzzzz
 */

#ifndef PUB_USERDATA1_H_
#define PUB_USERDATA1_H_

#include <string>
#include <vector>
#include "view.h"

namespace pub {

class user_data1___ {
public:
	std::string code_;
	void* shangji_;
	view___* view_;

	bool jieshi__(std::vector<std::string>* p);
	static bool jieshi2__(void* user_data, std::vector<std::string>* p = nullptr);
};

} /* namespace pub */

#endif /* PUB_USERDATA1_H_ */
