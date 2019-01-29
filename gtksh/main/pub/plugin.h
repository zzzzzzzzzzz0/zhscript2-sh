/*
 * plugin.h
 *
 *  Created on: 2017年8月4日
 *      Author: zzzzzzzzzzz
 */

#ifndef PUB_PLUGIN_H_
#define PUB_PLUGIN_H_

#include <string>
#include <vector>
#include "view.h"

namespace pub {

class plugin___ {
public:
	std::string name_;

	plugin___();
	virtual ~plugin___();
	virtual bool api__(void* shangji, const std::vector<std::string>& p, std::vector<data___>* p2, std::vector<std::string>& ret) {return false;}
	virtual view___* new_view__() {return new view___();}
};

} /* namespace pub */

#endif /* PUB_PLUGIN_H_ */
