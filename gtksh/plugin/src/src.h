/*
 * srcvw.h
 *
 *  Created on: 2017年8月27日
 *      Author: zzzzzzzzzzz
 */

#ifndef SRC_H_
#define SRC_H_

#include "pub/plugin.h"
#include "view.h"

class src___: public pub::plugin___ {
public:
	pub::view___* new_view__() {return new view___();}
};

#endif /* SRC_H_ */
