/*
 * view.cpp
 *
 *  Created on: 2020年04月09日
 *      Author: zzzzzzzzzzz
 */

#include "view.h"
#include "pub/sig.h"
#include "pub/tag.h"
#include "pub/ext.h"
#include "pub/plugin.h"
#include "wnck_pager.h"

static wnck_pager___ *plugin_ = nullptr;

static pub::tags___ tags_ = {
		{"仅名称", "dn", 0},
		{"竖向", "ov", 0},
		{"行数", "r", 1},
};

bool view___::api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret) {
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y':
		switch(tag[0]) {
		case 'd':
			switch(tag[1]) {
			//WNCK_PAGER_DISPLAY_CONTENT
			case 'n':
				wnck_pager_set_display_mode (hr__(), WNCK_PAGER_DISPLAY_NAME);
				break;
			}
			break;
		case 'o':
			switch(tag[1]) {
			//GTK_ORIENTATION_HORIZONTAL
			case 'v':
				wnck_pager_set_orientation (hr__(), GTK_ORIENTATION_VERTICAL);
				break;
			}
			break;
		case 'r':
			wnck_pager_set_n_rows (hr__(), std::stoi(p[1]));
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
}

static pub::sigs___ sigs_ = {
};

view___::view___() {
	hr_ = wnck_pager_new ();
	gtk_widget_set_size_request (hr_, 0, 0);
	//wnck_pager_set_show_all (hr__(), true);
	//wnck_pager_set_shadow_type (hr__(), GTK_SHADOW_IN);

	sigs_.conn__(hr_, this);
}

view___::~view___() {
}

extern "C" void ext__(pub::ext___* ext, pub::plugin___ *plugin) {
	pub::ext_ = ext;
	plugin_ = (wnck_pager___ *)plugin;
}
