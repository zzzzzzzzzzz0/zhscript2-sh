/*
 * webkit2.cpp
 *
 *  Created on: 2020年07月04日
 *      Author: zzzzzzzzzzz
 */

#include "webkit2.h"
#include "view.h"

pub::view___* webkit2___::new_view__() {
	return new view___();
}

webkit2___::webkit2___() {
}

webkit2___::~webkit2___() {
}

static webkit2___ plugin_;
extern "C" void *plugin__(const std::string &path) {return &plugin_;}
