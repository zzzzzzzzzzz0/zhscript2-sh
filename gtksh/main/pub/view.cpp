/*
 * view.cpp
 *
 *  Created on: 2017年8月5日
 *      Author: zzzzzzzzzzz
 */

#include "view.h"
#include "tag.h"
#include "ext.h"

namespace pub {

void view___::var__(const char *name, gpointer data) {
	g_object_set_data(object__(), name, data);
}
gpointer view___::var__(const char *name) {
	return g_object_get_data(object__(), name);
}

static pub::tags___ tags_ = {
		{"变量", "v", 1},
};

bool view___::api__(void* shangji, const std::vector<std::string>& p, std::vector<std::string>& ret) {
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y':
		switch(tag[0]) {
		case 'v': {
			std::string name = p[0] + p[1];
			if(p.size() > 2)
				var__(name.c_str(), (gpointer)p[2].c_str());
			else
				ret.push_back((const char*)var__(name.c_str()));
			break; }
		}
		return true;
	case '<':
		ext_->buzu__(p);
		return true;
	}
	return false;
}

} /* namespace pub */

