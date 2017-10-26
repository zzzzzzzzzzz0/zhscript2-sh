/*
 * srcvw.cpp
 *
 *  Created on: 2017年8月27日
 *      Author: zzzzzzzzzzz
 */

#include "src.h"

static src___ plugin_;
extern "C" void *plugin__(const std::string &path) {return &plugin_;}
