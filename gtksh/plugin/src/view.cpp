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
#include "pub/sig.h"
#include "pub/util.h"
#include "src.h"
#include <sys/stat.h>

#ifdef ver_debug_
#include "pub/debug.h"
pub::debug___ debug_;
#endif

static src___ *plugin_ = nullptr;

void view___::openfile__(const std::vector<std::string>& p, size_t from, bool no_undo, std::vector<std::string>* ret) {
	gchar *contents;
	gsize length;
	GError *error=NULL;
	if(g_file_get_contents(p[from].c_str(),&contents,&length,&error)){
		text_begin__(no_undo);
		gtk_text_buffer_set_text(buf2__(), contents, length);
		text_end__(no_undo);

		g_free(contents);
	}else{
		if (error != NULL) {
			if(ret)
				ret->push_back(error->message);
			g_clear_error(&error);
		}
	}
}
void view___::text_begin__(bool no_undo) {
	if(no_undo)
		gtk_source_buffer_begin_not_undoable_action(buf_);
}
void view___::text_end__(bool no_undo) {
	if(no_undo) {
		GtkTextIter ti;
		gtk_text_buffer_get_iter_at_offset(buf2__(), &ti, 0);
		gtk_text_buffer_place_cursor(buf2__(), &ti);

		gtk_source_buffer_end_not_undoable_action(buf_);
	}
	gtk_text_buffer_set_modified(buf2__(), false);
}
bool view___::text_opti__(const std::vector<std::string>& p, bool& no_undo) {
	for(size_t i = 2; i < p.size(); i++) {
		const std::string& p3=p[i];
		if(p3 == "可撤销") {
			no_undo = false;
			continue;
		}
		pub::ext_->buzhichi__(p, i);
		return false;
	}
	return true;
}

static void cb_modified_changed__ (GtkTextBuffer *textbuffer, gpointer user_data) {
	pub::ext_->jieshi22__(user_data, "s", gtk_text_buffer_get_modified(textbuffer) ? "1" : "");
}

static void drag_data_received__(GtkWidget *widget,
		GdkDragContext *context,
		gint x,gint y,
		GtkSelectionData *data,
		guint info,
		guint time,
		gpointer user_data)
{
	pub::sign___* sign = (pub::sign___*)user_data;
	view___* view = (view___*)sign->data_;
	GdkAtom atom=gtk_selection_data_get_data_type(data);
	if(gtk_targets_include_uri(&atom,1)) {
		/*gchar **uris=gtk_selection_data_get_uris(data);
		gint i=0;
		while(uris[i]!=NULL) {
			chuli__(code, uris[i++]);
		}
		g_strfreev(uris);*/
	} else {
		gchar *uris = (gchar *)gtk_selection_data_get_text (data);
		if(uris) {
			std::vector<std::string> p, ret;
			p.push_back(uris);
			g_free (uris);
			if(pub::ext_->jieshi__(nullptr, view, sign->code_.c_str(), nullptr, nullptr, false, &p, nullptr, &ret)) {
				if(ret.size() == 1) {
					const std::string& s = ret[0];
					char* s2 = new char[s.length() + 1];
					s.copy(s2, s.length());
					s2[s.length()] = 0;
					gtk_selection_data_set_text (data, s2, s.length());
					gtk_drag_finish(context,TRUE,TRUE,time);
				}
			}
		}
	}
}

static pub::sigs___ sigs2_ = {
		{"modified-changed", G_CALLBACK(cb_modified_changed__), "已修改"/*nullptr, 'm'*/},
};

static pub::sigs___ sigs3_ = {
		{"drag-data-received", G_CALLBACK(drag_data_received__), "拖放"},
};

static pub::tags___ tags_ = {
		{"插入", "i", 1},
		{"光标位置", "p", 0},
		{"光标行列", "l", 0},
		{"选择", " s", 0},
		{"搜", "S", 1},
		{"已修改", "m", 0},
		{"剪切", "x", 0},
		{"复制", "c", 0},
		{"粘贴", "v", 0},
		{"撤销", "u", 0},
		{"重做", "r", 0},
		{"缩进用空格", "I", 0},
		{"语法高亮", "h", 1},
		{"内容", " ", 0},
		{"打开文件", "o", 1},
		{"保存文件", "s", 1},
		{"刷新", "R", 0},
		{"不可编辑", "E", 0},
		{"侦听", "z", 0},
};

bool view___::api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret) {
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y':
		switch(tag[0]) {
		case 'i': {
			GtkTextIter i1;
			bool i1_has_use = false;
			if(p.size() > 2) {
				const std::string& p3 = p[1];
				i1_has_use = true;
				if(p3 == "头")
					gtk_text_buffer_get_start_iter (buf2__(), &i1);
				else if(p3 == "尾")
					gtk_text_buffer_get_end_iter (buf2__(), &i1);
				else {
					pub::ext_->buzhichi__(p, 1);
					return true;
				}
			}
			if(!i1_has_use) {
				GtkTextIter i2;
				gtk_text_buffer_get_selection_bounds (buf2__(), &i1, &i2);
				if(gtk_text_iter_get_offset (&i2) > gtk_text_iter_get_offset (&i1)){
					gtk_text_buffer_delete(buf2__(), &i1,&i2);
				}
			}
			const std::string& s = p[p.size() - 1];
			gtk_text_buffer_insert (buf2__(), &i1, s.c_str(), s.size());
			scroll2__(&i1);
			break; }
		case'p':
		case'l': {
			GtkTextIter ti;
			gtk_text_buffer_get_iter_at_mark (buf2__(), &ti, gtk_text_buffer_get_insert (buf2__()));
			if(tag[0]=='l'){
				int line = gtk_text_iter_get_line (&ti), line_offset=gtk_text_iter_get_line_offset (&ti);
				if(p.size() == 1) {
					ret.push_back(std::to_string(line));
					ret.push_back(std::to_string(line_offset));
				} else {
					if(p.size()>1)
						gtk_text_iter_set_line (&ti, pub::stoi__(p[1], line));
					if(p.size()>2)
						gtk_text_iter_set_line_offset (&ti, pub::stoi__(p[2], line_offset));
					scroll2__(&ti);
				}
			} else {
				int offset = gtk_text_iter_get_offset (&ti);
				if(p.size()>1){
					int i = pub::stoi__(p[1],offset);
					if(i < 0) {
						GtkTextIter end;
						gtk_text_buffer_get_end_iter (buf2__(), &end);
						i += gtk_text_iter_get_offset (&end) + 1;
					}
					gtk_text_iter_set_offset (&ti, i);
					scroll2__(&ti);
				}else
					ret.push_back(std::to_string(offset));
			}
			break; }
		case 'S': {
			const std::string &s = p[1];
			if(s.empty())
				break;
			bool forward = true;
			GtkTextSearchFlags tsf = GtkTextSearchFlags(GTK_TEXT_SEARCH_TEXT_ONLY | GTK_TEXT_SEARCH_CASE_INSENSITIVE);
			for(size_t i = 2; i < p.size(); i++) {
				const std::string s = p[i];
				if(s == "反向") {
					forward = false;
					continue;
				}
				if(s == "大小写") {
					tsf = GTK_TEXT_SEARCH_TEXT_ONLY;
					continue;
				}
				pub::ext_->buzhichi__(p, i);
				return true;
			}
			GtkTextIter ti, ti2;
			GtkTextIter *ti3;
			gtk_text_buffer_get_selection_bounds (buf2__(), &ti, &ti2);
			ti3 = forward ? &ti2 : &ti;
			if (forward ?
					gtk_text_iter_forward_search (ti3, s.c_str(), tsf,  &ti, &ti2, nullptr)
					:
					gtk_text_iter_backward_search (ti3, s.c_str(), tsf,  &ti, &ti2, nullptr)) {
				ti3 = forward ? &ti2 : &ti;
				gtk_text_buffer_select_range (buf2__(), &ti, &ti2);
				scroll2__(ti3, false);
				gtk_widget_grab_focus (widget__());
				ret.push_back("1");
			}
			break; }
		case'm':
			if(p.size()>1){
				const std::string&s=p[1];
				if(s=="侦听"){
					if(p.size() == 2) {
						pub::ext_->buzu__(p, SIZE_MAX);
						return true;
					}
					sigs2_.conn__(p[0]/*'m'*/, buf2__(), this, p[2].c_str());
				}else
					gtk_text_buffer_set_modified(buf2__(), pub::bool__(s));
			}else {
				if(gtk_text_buffer_get_modified(buf2__()))
					ret.push_back("1");
			}
			break;
		case'x':
		case'c':
		case'v': {
			GtkClipboard *cb = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
			switch(tag[0]){
			case'x': gtk_text_buffer_cut_clipboard(buf2__(), cb, true); break;
			case'c': gtk_text_buffer_copy_clipboard(buf2__(), cb); break;
			case'v': gtk_text_buffer_paste_clipboard(buf2__(), cb, NULL, true); break;
			}
			break; }
		case 'u':
			if(!gtk_source_buffer_can_undo(buf_)) {
				pub::ext_->wufa__(p, SIZE_MAX);
				return true;
			}
			gtk_source_buffer_undo(buf_);
			break;
		case 'r':
			if(!gtk_source_buffer_can_redo(buf_)) {
				pub::ext_->wufa__(p, SIZE_MAX);
				return true;
			}
			gtk_source_buffer_redo(buf_);
			break;
		case 'I':
			gtk_source_view_set_insert_spaces_instead_of_tabs(hr__(), true);
			break;
		case'h':
			if(p.size()>1){
				const std::string &id = p[1];
				if(!id.empty()) {
					GtkSourceLanguageManager *slm = gtk_source_language_manager_get_default ();
					GtkSourceLanguage *sl = gtk_source_language_manager_get_language (slm, id.c_str());
					if(sl){
						gtk_source_buffer_set_language (buf_, sl);
						gtk_source_buffer_set_highlight_syntax(buf_, true);
						break;
					}
					pub::ext_->buzhichi__(p, SIZE_MAX);
					return true;
				}
			}
			gtk_source_buffer_set_highlight_syntax(buf_, false);
			break;
		case ' ':
			if(p.size() > 1) {
				const std::string&s=p[1];
				bool no_undo = true;
				if(!text_opti__(p, no_undo))
					return true;
				text_begin__(no_undo);
				switch(tag[1]) {
				case 's':
					break;
				default:
					gtk_text_buffer_set_text(buf2__(), s.c_str(), s.size());
					break;
				}
				text_end__(no_undo);
			} else {
				char* text = text__(tag[1] == 's');
				ret.push_back(text);
				g_free (text);
			}
			break;
		case 'o': {
			bool no_undo = true;
			if(!text_opti__(p, no_undo))
				return true;
			openfile__(p, 1, no_undo, &ret);
			break; }
		case 's': {
			GError *error = NULL;
			const std::string& filename = p[1];
			char* text = text__();
			struct stat st;
			int st_err = stat(filename.c_str(), &st);
			g_file_set_contents (filename.c_str(), text, -1, &error);
			if (error != NULL) {
				ret.push_back(error->message);
				g_clear_error(&error);
			} else {
				if(!st_err)
					chmod(filename.c_str(), st.st_mode);
				gtk_text_buffer_set_modified(buf2__(), false);
			}
			g_free (text);
			break; }
		case 'R':
			if(gtk_text_buffer_get_modified(buf2__())) {
				pub::ext_->err__("已修改");
				return true;
			}
			reinit__();
			break;
		case 'E':
			gtk_text_view_set_editable(hr2__(), false);
			break;
		case 'z':
			for(size_t i = 1; i < p.size(); i += 2) {
				const std::string& p1 = p[i];
				size_t i1 = i + 1;
				if(i1 >= p.size()) {
					pub::ext_->buzu__(p, SIZE_MAX);
					return true;
				}
				if(sigs3_.conn__(p1, hr_, this, p[i1].c_str()))
					continue;
				pub::ext_->buzhichi__(p, i);
				return true;
			}
			break;
		}
		return true;
	case '<':
		pub::ext_->buzu__(p, SIZE_MAX);
		return true;
	}
	return pub::view___::api__(shangji, p, p2, ret);
}

void view___::new_open__(const std::vector<std::string>& p, bool is_new) {
	if(p.size() > 0 && !p[0].empty()) {
		openfile__(p, 0, is_new, nullptr);
	}
}

char* view___::text__(bool is_sel) {
	GtkTextIter start, end;
	if(is_sel)
		gtk_text_buffer_get_selection_bounds (buf2__(), &start, &end);
	else {
		gtk_text_buffer_get_start_iter (buf2__(), &start);
		gtk_text_buffer_get_end_iter (buf2__(), &end);
	}
	return gtk_text_buffer_get_text (buf2__(), &start, &end, FALSE);
}

void view___::scroll2__(GtkTextIter* ti, bool place) {
	if(place)
		gtk_text_buffer_place_cursor(buf2__(), ti);

	/*GtkTextIter i1,i2;
	gtk_text_buffer_get_selection_bounds (buf2__(), &i1,&i2);
	GdkRectangle rect;
	gtk_text_view_get_visible_rect (hr2__(), &rect);
	int y = -1, height = -1;
	gtk_text_view_get_line_yrange (hr2__(), &i1, &y, &height);
	if (y < rect.y || y > rect.y + rect.height)*/ {
		/*GSList *ls = gtk_text_iter_get_marks (ti);
		GtkTextMark *tm = (GtkTextMark*)ls->data;
		gtk_text_view_scroll_to_mark (hr2__(), tm, 0, false, 0, 0);
		g_slist_free(ls);*/
		gtk_text_view_scroll_to_iter (hr2__(), ti, 0, false, 0, 0);
	}
	//gtk_text_view_scroll_mark_onscreen (hr2__(), gtk_text_buffer_get_insert(buf2__()));
}

static pub::sigs___ sigs_ = {
};

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
	//gtk_widget_set_can_focus(hr_, true);

	sw_ = gtk_scrolled_window_new (NULL, NULL);
	GtkScrolledWindow *sw1 = GTK_SCROLLED_WINDOW(sw_);
	gtk_scrolled_window_set_policy (sw1, GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_container_add (GTK_CONTAINER (sw_), hr_);

	sigs_.conn__(hr_, this);
}

view___::~view___() {
	sigs_.del__(hr_, this);
	sigs2_.del__(buf2__(), this);
	sigs3_.del__(hr_, this);
}

extern "C" void ext__(pub::ext___* ext, pub::plugin___ *plugin) {
	pub::ext_ = ext;
	plugin_ = (src___ *)plugin;
}
