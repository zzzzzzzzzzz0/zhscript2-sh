/*
 * vte.h
 *
 *  Created on: 2017年09月12日
 *      Author: zzzzzzzzzzz
 */

#ifndef VTE_H_
#define VTE_H_

#include "pub/plugin.h"

class vte___: public pub::plugin___ {
public:
	std::string arg1_, env1_, cmd1_;

	bool api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret);
	pub::view___* new_view__();
};

#endif /* VTE_H_ */
