/*
 * base.cpp
 *
 *  Created on: 2017年12月22日
 *      Author: zzzzzzzzzzz
 */

#include "base.h"

namespace pub {

void base___::var__(const char *name, gpointer data) {
	g_object_set_data(object__(), name, data);
}
gpointer base___::var__(const char *name) {
	return g_object_get_data(object__(), name);
}

void base___::name__(const char *name) {
	//gtk_widget_set_name(widget__(), name);
	name_ = name;
}
const char *base___::name__() {
	//return gtk_widget_get_name(widget__());
	return name_.c_str();
}

void base___::var__(const std::vector<std::string>& p, std::vector<std::string>& ret) {
	std::string name = p[1];
	if(p.size() > 2) {
		var_[name] = p[2];
	} else {
		if(var_.find(name) != var_.end())
			ret.push_back(var_[name]);
	}
}

} /* namespace pub */
