/*
 * view.cpp
 *
 *  Created on: 2017年8月27日
 *      Author: zzzzzzzzzzz
 */

#include "view.h"
#include "pub/ext.h"
#include "pub/plugin.h"
#include "pub/tag.h"

static pub::tags___ tags_ = {
		{"内容", " ", 0},
};

bool view___::api__(void* shangji, const std::vector<std::string>& p, std::vector<std::string>& ret) {
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y':
		switch(tag[0]) {
		case ' ':
			GtkTextIter start, end;
			gtk_text_buffer_get_start_iter (buf2__(), &start);
			gtk_text_buffer_get_end_iter (buf2__(), &end);
			ret.push_back(gtk_text_buffer_get_text (buf2__(), &start, &end, FALSE));
			break;
		}
		return true;
	case '<':
		pub::ext_->buzu__(p);
		return true;
	}
	return pub::view___::api__(shangji, p, ret);
}

void view___::new_open__(const std::vector<std::string>& p) {
}

view___::view___() {
	buf_ = GTK_SOURCE_BUFFER (gtk_source_buffer_new (NULL));

	hr_ = gtk_source_view_new_with_buffer(buf_);

	GtkSourceView* sv = hr__();
	gtk_source_view_set_show_line_numbers(sv, true);
	gtk_source_view_set_tab_width(sv, 4);
	gtk_source_view_set_auto_indent (sv, true);
	gtk_source_view_set_smart_home_end(sv, GTK_SOURCE_SMART_HOME_END_ALWAYS);
	gtk_source_view_set_draw_spaces (sv, GTK_SOURCE_DRAW_SPACES_ALL);
	gtk_source_view_set_smart_backspace (sv, true);
	gtk_widget_set_can_focus(hr_, true);
}

view___::~view___() {
}

extern "C" void ext__(pub::ext___* ext, pub::plugin___ *plugin) {
	pub::ext_ = ext;
}
