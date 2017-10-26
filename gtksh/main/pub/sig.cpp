/*
 * sig.cpp
 *
 *  Created on: 2017年8月5日
 *      Author: zzzzzzzzzzz
 */

#include "sig.h"
#include <map>
#include <vector>

namespace pub {

void sig___::conn__(gpointer p1, sign___* p2) {
	if(p2)
		p2->sig_ = this;
	id_ = g_signal_connect(p1, coname_, cb_, p2 ? (gpointer)p2 : this);
}
void sig___::disconn__(gpointer p1) {
	if(id_) {
		g_signal_handler_disconnect(p1, id_);
		id_ = 0;
	}
}

static std::map<gpointer, std::vector<sign___*>> map_;

void sigs___::conn__(gpointer p1, gpointer p2) {
	for(size_t i2 = 0; i2 < a_.size(); i2++) {
		sig___ *i = &a_[i2];
		sign___* sign = nullptr;
		if(p2) {
			sign = new sign___ {p2};
			map_[p2].push_back(sign);
		}
		i->conn__(p1, sign);
	}
}

void sigs___::del__(gpointer p1, gpointer p2) {
	if(p1)
		for(auto i : a_) {
			i.disconn__(p1);
		}
	if(p2) {
		auto i = map_.find(p2);
		if(i != map_.end()) {
			std::vector<sign___*> &a = i->second;
			for(size_t i2 = 0; i2 < a.size(); i2++)
				delete a[i2];
		}
	}
}

} /* namespace pub */

