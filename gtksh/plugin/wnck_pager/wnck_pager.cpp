/*
 * wnck_pager.cpp
 *
 *  Created on: 2020年04月09日
 *      Author: zzzzzzzzzzz
 */

#include "wnck_pager.h"
#include "view.h"

pub::view___* wnck_pager___::new_view__() {
	return new view___();
}

wnck_pager___::wnck_pager___() {
}

wnck_pager___::~wnck_pager___() {
}

static wnck_pager___ plugin_;
extern "C" void *plugin__(const std::string &path) {return &plugin_;}
