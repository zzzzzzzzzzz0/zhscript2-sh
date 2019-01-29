/*
 * userdata1.cpp
 *
 *  Created on: 2017年12月22日
 *      Author: zzzzzzzzzzz
 */

#include "userdata1.h"
#include "ext.h"

namespace pub {

bool user_data1___::jieshi__(std::vector<std::string>* p) {
	return pub::ext_->jieshi__(nullptr, view_, code_.c_str(), nullptr,
			/*shangji_*/nullptr, false, p, nullptr, nullptr);
}

bool user_data1___::jieshi2__(void* user_data, std::vector<std::string>* p) {
	user_data1___* data = (user_data1___*)user_data;
	return data->jieshi__(p);
}

} /* namespace pub */
