/*
 * cairog.h
 *
 *  Created on: 2018年01月21日
 *      Author: zzzzzzzzzzz
 */

#ifndef CAIROG_H_
#define CAIROG_H_

#include "pub/plugin.h"

class cairog___: public pub::plugin___ {
public:
	cairog___();
	virtual ~cairog___();

	bool api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret);
	pub::view___* new_view__();
};

#endif /* CAIROG_H_ */