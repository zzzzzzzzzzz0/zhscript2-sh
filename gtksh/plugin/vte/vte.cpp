/*
 * vte.cpp
 *
 *  Created on: 2017年09月12日
 *      Author: zzzzzzzzzzz
 */

#include "vte.h"
#include "view.h"

pub::view___* vte___::new_view__() {
	return new view___();
}

vte___::vte___() {
}

vte___::~vte___() {
}

static vte___ plugin_;
extern "C" void *plugin__(const std::string &path) {return &plugin_;}
