/*
 * view.cpp
 *
 *  Created on: 2020年07月04日
 *      Author: zzzzzzzzzzz
 */

#include "view.h"
#include "pub/sig.h"
#include "pub/tag.h"
#include "pub/ext.h"
#include "pub/plugin.h"
#include "pub/area.h"
#include "webkit2.h"

static webkit2___ *plugin_ = nullptr;

static pub::tags___ tags_ = {
		//{"内容", " ", 1},
};

bool view___::api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret) {
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y':
		switch(tag[0]) {
		case ' ':
			break;
		}
		return true;
	case '<':
		pub::ext_->buzu__(p, SIZE_MAX);
		return true;
	}
	return pub::view___::api__(shangji, p, p2, ret);
}

void view___::new_open__(const std::vector<std::string>& p) {
	webkit_web_view_load_uri(hr__(), "https://baidu.com");
}

GtkWidget*
cb_create__ (WebKitWebView          *web_view,
               WebKitNavigationAction *navigation_action,
               gpointer                user_data) {
	view___* v = new view___(web_view);
	pub::add_opt___ opt;
	std::vector<std::string> p;
	pub::sign___* sign = (pub::sign___*)user_data;
	pub::sig___* sig = sign->sig_;
	view___* v2 = (view___*)sign->data_;
	pub::add_opt___* opt2 = &((pub::area___*)v2->area_)->opt_;
	opt.copy__(opt2);
	if(opt2->pos_ == 'c' && !opt2->typ_)
		opt.new_window_ = true;
	if(pub::ext_->add_begin__(v, v2->window_, v2, &opt)) {
		pub::ext_->add_end__(v, nullptr, &opt, &p, plugin_);
	}
	return v->widget__();
}

static pub::sigs___ sigs_ = {
		{"create", G_CALLBACK(cb_create__), "新开"},
};

view___::view___(WebKitWebView* rv) {
	if(rv)
		hr_ = webkit_web_view_new_with_related_view(rv);
	else
		hr_ = webkit_web_view_new();

	sigs_.conn__(hr_, this);
}

view___::~view___() {
}

extern "C" void ext__(pub::ext___* ext, pub::plugin___ *plugin) {
	pub::ext_ = ext;
	plugin_ = (webkit2___ *)plugin;
}
