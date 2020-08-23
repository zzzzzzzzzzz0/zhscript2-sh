/*
 * window.cpp
 *
 *  Created on: 2017年8月5日
 *      Author: zzzzzzzzzzz
 */

#include "window.h"
#include "pub/sig.h"
#include "pub/tag.h"
#include "err.h"
#include "add.h"
#include "pub/ext.h"
#include "pub/util.h"
#include <gdk/gdkx.h>
#include "util.h"

#include "liandong.h"
static liandong___ liandong_;

#include "pub/eventget.h"
static pub::event_get___ event_get_;

static void x__(int &x, int no, int i_x, int* out, bool is, int w2) {
	int w = is ? gdk_screen_width() : gdk_screen_height();
	int max = w - w2;
	if(out) {
		if(x < 0) *out = x;
		//else if(x >= w) *out = x - w + 1;
		else if(x > max) *out = x - max;
	}
	switch(no) {
	case 2: {
		if(x >= max) {
			x = max;
			return;
		}
		break; }
	}
	if(x >= 0) {
		return;
	}
	switch(no) {
	case 1: case 2:
		x = 0;
	case -1:
		return;
	}
	switch(no) {
	case -2:
		x = (w + x) / i_x;
		return;
	}
	if(x + w > 0) {
		x += w;
		return;
	}
}
void window___::stoi__(const std::vector<std::string>& p, int& x, int& y, int* out_x, int* out_y) {
	x = pub::stoi__(p[1], x);
	y = p.size() > 2 ?
		pub::stoi__(p[2], y) : x;
	int no_x = 0, no_y = 0, i_x = 0, i_y = 0;
	switch(p.size()) {
	case 4:
		no_x = no_y = p[3].empty() ? 1 : (p[3] == "2" ? pub::stoi__(p[3]) : -1);
		break;
	case 5:
		if(!p[3].empty()) {
			no_x = -2;
			i_x = pub::stoi__(p[3]);
		}
		if(!p[4].empty()) {
			no_y = -2;
			i_y = pub::stoi__(p[4]);
		}
		if(i_x <= 0) i_x = 1;
		if(i_y <= 0) i_y = 1;
		break;
	}
	x__(x, no_x, i_x, out_x, true, width_);
	x__(y, no_y, i_y, out_y, false, height_);
}

static pub::tags___ tags_ = {
		{"移动", "m", 0},
		{"标题", "t", 0},
		{"图标", "i", 1},
		//{"显现", "S", 0},
		{"隐藏", "h", 0},
		{"居中", "c", 0},
		{"最大化", "A", 0},
		{"最小化", "I1", 0},
		{"取消最小化", "I", 0},
		{"大小", "s", 0},
		{"宽高", "s", 0},
		{"预宽高", "sd", 0},
		{"定宽高", "sr", 0},
		{"置顶", "T1", 0},
		{"取消置顶", "T", 0},
		{"置底", "B1", 0},
		{"取消置底", "B", 0},
		{"总可见"/*粘滞*/, "D1", 0},
		{"取消总可见", "D", 0},
		{"所有桌面", "D1", 0},
		{"取消所有桌面", "D", 0},
		{"全屏", "F1", 0},
		{"取消全屏", "F", 0},
		{"光标形状", "^", 0},
		{"窗背景色", "b", 1},
		{"窗句柄", "H", 0},
		{"xid", "X", 0},
		{"关闭", "x", 0},
		{"窗变量", "v", 1},
		{"遍历", "f", 1},
		{"联动", "-", 1},
		{"修饰宽高", "[", 0},
		{"类名", "C", 1},
		{"禁宽高", "!s", 0}, //最大化按钮去
		{"禁关闭", "!x", 0},
		{"不在任务栏", "!t", 0},
		{"不透明度", "!o", 1},
		{"鼠标穿透", "!m", 0},
		{"只有关闭钮", "!X", 0},
		{"无标题栏", "!T", 0},
		{"无修饰", "d", 0},
		{"窗事件", "e", 0},
};

bool window___::api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret) {
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y':
		switch(tag[0]) {
		case 'm': {
			int x, y;
			gtk_window_get_position(hr__(), &x, &y);
			if(p.size() > 1) {
				int out_x = 0, out_y = 0;
				stoi__(p, x, y, &out_x, &out_y);
				switch(p.size()) {
				case 4: {
					const std::string& s = p[3];
					if(s[0] == '0' && (out_x != 0 || out_y != 0)) {
						std::vector<std::string> p3, p4;
						p4.push_back(std::to_string(out_x));
						p4.push_back(std::to_string(out_y));
						pub::ext_->jieshi__(this, nullptr, s.substr(1).c_str(), nullptr, nullptr, false, &p4, nullptr, &p3);
						if(pub::bool__(p3, 0, false))
							return true;
					}
					break; }
				}
				gtk_window_move(hr__(), x, y);
			} else {
				ret.push_back(std::to_string(x));
				ret.push_back(std::to_string(y));
			}
			break; }
		case 't':
			if(p.size() > 1)
				gtk_window_set_title(hr__(), p[1].c_str());
			else {
				const char* s = gtk_window_get_title(hr__());
				if(s)
					ret.push_back(s);
			}
			break;
		case 'i': {
			const std::string& name = p[1];
			GdkPixbuf* pb;
			if(p.size() > 2)
				pb = gtk_icon_theme_load_icon(gtk_icon_theme_get_default(), name.c_str(), std::atoi(p[2].c_str()),
						GTK_ICON_LOOKUP_USE_BUILTIN, nullptr);
			else
				pb = gdk_pixbuf_new_from_file(name.c_str(), nullptr);
			if(!pb) {
				err_.wufa__(p);
				return true;
			}
			gtk_window_set_icon_name(hr__(), name.c_str());
			gtk_window_set_icon(hr__(), pb);
			break; }
		//case 'S': gtk_widget_show(widget__()); break;
		case 'h': gtk_widget_hide(widget__()); break;
		case 'c':
			gtk_window_set_position(hr__(),GTK_WIN_POS_CENTER);
			break;
		case 'A': gtk_window_maximize (hr__()); break;
		case 'I':
#ifdef ver_debug_
			debug_.o__(tag, " ", name__(), " ", p[0]);
#endif
			if(tag[1]) gtk_window_iconify (hr__());
			else     gtk_window_deiconify (hr__());
			break;
		case 's': {
			gint w, h;
			gtk_window_get_size (hr__(), &w, &h);
			if(p.size() > 1) {
				stoi__(p, w, h);
				switch(tag[1]) {
				default:
					gtk_window_resize(hr__(), w, h);
					break;
				case 'd':
					gtk_window_set_default_size (hr__(), w, h);
					break;
				case 'r':
					gtk_widget_set_size_request (hr_, w, h);
					break;
				}
			} else {
				ret.push_back(std::to_string(w));
				ret.push_back(std::to_string(h));
				gtk_window_get_default_size (hr__(), &w, &h);
				ret.push_back(std::to_string(w));
				ret.push_back(std::to_string(h));
			}
			break; }
		case 'T':
			gtk_window_set_keep_above (hr__(), tag[1]);
			break;
		case 'B':
			gtk_window_set_keep_below (hr__(), tag[1]);
			break;
		case 'D':
			if(tag[1])
				gtk_window_stick(hr__());
			else
				gtk_window_unstick(hr__());
			break;
		case 'F':
			if(tag[1])
				gtk_window_fullscreen(hr__());
			else
				gtk_window_unfullscreen(hr__());
			break;
		case '^':
			if(cursor_) {
				gdk_cursor_unref(cursor_);
			}
			if(p.size() > 1) {
				const std::string& p2 = p[1];
				int i;
				if(p2 == "移动")
					i = GDK_FLEUR;
				else if(sscanf(p2.c_str(), "%d", &i) != 1) {
					err_.buzhichi__(p);
					return true;
				}
				cursor_ = gdk_cursor_new((GdkCursorType)i);
				if(!cursor_) {
					err_.buzhichi__(p);
					return true;
				}
			} else {
				cursor_ = NULL;
			}
			gdk_window_set_cursor(hr2__(), cursor_);
			break;
		case 'b': {
			GdkColor color;
			gdk_color_parse(p[1].c_str(), &color);
			gdk_window_set_background(hr2__(), &color);
			break; }
		case 'H':
			ret.push_back(std::to_string((unsigned long)hr_));
			break;
		case 'X': {
			GdkWindow *w = hr2__();
			if(w)
				ret.push_back(std::to_string(GDK_WINDOW_XID(w)));
			break; }
		case 'x':
			this->destroy__();
			break;
		case 'v':
			var__(p, ret);
			break;
		case 'f': {
			std::string ret2;
			add___::for_view__(this, [&](pub::view___* v) {
				std::vector<std::string> ret3;
				bool ret4 = pub::ext_->jieshi__(nullptr, v, p[1].c_str(), nullptr, shangji, false, nullptr, nullptr, &ret3);
				if(ret3.size() > 0) ret2 += ret3[0];
				return ret4;
			});
			if(!ret2.empty()) ret.push_back(ret2);
			break; }
		case '[': {
			if(!liandong_pian_.get_) {
				liandong_pian_.get__(this, x_, y_);
			}
			ret.push_back(std::to_string(liandong_pian_.x_));
			ret.push_back(std::to_string(liandong_pian_.y_));
			break; }
		case '!':
			switch(tag[1]) {
			case 't': gtk_window_set_skip_taskbar_hint(hr__(), true); break;
			case 'o': gtk_window_set_opacity(hr__(), std::stof(p[1])); break;
			case 'm': util___::chuantou__(widget__()); break;
			case 's': gtk_window_set_resizable(hr__(), false); break;
			case 'x': gtk_window_set_deletable(hr__(), false); break;
			case 'X': gtk_window_set_type_hint(hr__(), GDK_WINDOW_TYPE_HINT_UTILITY); break;
			case 'T': gtk_window_set_type_hint(hr__(), GDK_WINDOW_TYPE_HINT_DIALOG); break;
			}
			break;
		case 'd':
			gtk_window_set_decorated(hr__(), !pub::bool__(p, 1, true));
			break;
		case '-':
			liandong_.add__(this, p[1]);
			break;
		case 'C': {
			const std::string& cn = p[1];
			const std::string& cc = p[p.size() > 2 ? 2 : 1];
			gtk_window_set_wmclass(hr__(), cn == null_ ? NULL : cn.c_str(), cc == null_ ? NULL : cc.c_str());
			break; }
		case 'e':
			switch(event_get_.api__(p, object__())) {
			case '<':
				err_.buzu__(p);
				return true;
			}
			break;
		}
		return true;
	case '<':
		err_.buzu__(p);
		return true;
	}
	return false;
}

static void cb_destroy__(GtkWidget* widget, gpointer user_data) {
	pub::sign___* sign = (pub::sign___*)user_data;
	if(sign != sign->this_) {
		pub::ext_->err__("cb_destroy__ sign");
		return;
	}
	pub::sig___* sig = sign->sig_;
	sig->disconn__(widget);
	window___* w = (window___*)sign->data_;
	if(w != sign->this_data_) {
		pub::ext_->err__("cb_destroy__ sign.data");
		return;
	}
	pub::ext_->jieshi21__(w, w->is_main__() ? "销毁" : sig->name_);
	liandong_.window_destroy__(w);
	if(w->is_main__())
		gtk_main_quit();
	delete w;
}

static gboolean cb_delete_event__(GtkWidget *widget, GdkEvent *event, gpointer gdata) {
	pub::sign___* sign = (pub::sign___*)gdata;
	window___* w = (window___*)sign->data_;
	pub::sig___* sig = sign->sig_;
	std::vector<std::string> p, p2;
	p2.push_back(w->name__());
	if(w->is_main__())
		p2.push_back("1");
	pub::ext_->jieshi__(w, nullptr, nullptr, sig->name_, nullptr, false, &p2, nullptr, &p);
	return pub::bool__(p, 0, false);
}

static gboolean cb_configure_event__(GtkWidget *widget, GdkEventConfigure *event, gpointer user_data) {
	window___* win = (window___*)((pub::sign___*)user_data)->data_;
	int x = event->x, y = event->y;
	if(win->x_ != x || win->y_ != y) {
		win->x_ = x;
		win->y_ = y;
		int x2, y2;
		gtk_window_get_position(GTK_WINDOW(widget), &x2, &y2);
		pub::ext_->jieshi2__(add___::get_view__(nullptr, win), "移动", "iiii", x, y, x2, y2);
	}
	int w = event->width, h = event->height;
	if(win->width_ != w || win->height_ != h) {
		switch(win->width_) {
		case -1:
			break;
		default:
			/*{ //原来返回TRUE
				GList *ls = gtk_container_get_children(win->container__());
				for (GList *i = ls; i; i = i->next) {
					GtkWidget *wid = GTK_WIDGET(i->data);
					gtk_widget_queue_resize (wid);
				}
				g_list_free(ls);
			}*/
			liandong_.window_resize__(win, w, win->width_, h, win->height_);
			break;
		}
		win->width_ = w;
		win->height_ = h;
		pub::ext_->jieshi2__(add___::get_view__(nullptr, win), "宽高", "ii", w, h);
	}
	liandong_.window_move__(win, x, y);
	return false;
}

static gboolean cb_window_state_event__(GtkWidget *widget, GdkEventWindowState *event, gpointer user_data) {
	GdkWindowState ws = event->new_window_state;
	pub::sign___* sign = (pub::sign___*)user_data;
	pub::sig___* sig = sign->sig_;
	window___* w = (window___*)sign->data_;
	liandong_.window_state__(w, ws);
	std::string s1;
	if ((ws & GDK_WINDOW_STATE_FULLSCREEN))
		s1 += "全屏";
	if((ws & GDK_WINDOW_STATE_MAXIMIZED))
		s1 += "最大化";
	if((ws & GDK_WINDOW_STATE_ICONIFIED))
		s1 += "最小化";
	if((ws & GDK_WINDOW_STATE_ABOVE))
		s1 += "置顶";
	if((ws & GDK_WINDOW_STATE_BELOW))
		s1 += "置底";
	if((ws & GDK_WINDOW_STATE_STICKY))
		s1 += "总可见";
	if((ws & GDK_WINDOW_STATE_TILED))
		s1 += "平铺";
	if(w->state_ != s1) {
		w->state_ = s1;
		pub::ext_->jieshi2__(add___::get_view__(nullptr, w), sig->name_, "s", s1.c_str());
	}
	return false;
}

static pub::sigs___ sigs_ = {
		{"destroy", G_CALLBACK(cb_destroy__), "关闭"},
		{"delete-event", G_CALLBACK(cb_delete_event__), "当关闭"},
		{"configure_event", G_CALLBACK(cb_configure_event__)},
		{"window-state-event", G_CALLBACK(cb_window_state_event__), "状态"},
};

void window___::destroy__() {
	//g_signal_emit_by_name(widget__(), "delete-event"/*"destroy"*/);
	gtk_widget_destroy(widget__());
}

void window___::app_paintable__(GtkWidget *hr) {
	if(!hr) hr = hr_;
	gtk_widget_set_app_paintable(hr, TRUE);
	GdkScreen *screen = gtk_widget_get_screen(hr);
	GdkVisual *visual = gdk_screen_get_rgba_visual(screen);
	if (!visual)
		visual = gdk_screen_get_system_visual(screen);
	gtk_widget_set_visual(hr, visual);
}

std::vector<window___*> windows_;

window___::~window___() {
	for(auto i = windows_.begin(); i != windows_.end(); i++)
		if(*i == this) {
			windows_.erase(i);
			break;
		}
	sigs_.del__(hr_, this);
	liandong_.del__(this);
	{
		add___* add = (add___*)add_;
		add->del__(this);
		delete add;
	}
}

static int i_ = 0;

window___::window___(bool is_app_paintable, bool is_main) : is_main_(is_main) {
	add_ = new add___();
	hr_ = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	name__(("窗" + std::to_string(++i_)).c_str());
	if(is_app_paintable) {
		app_paintable__(hr_);
	}
	sigs_.conn__(hr_, this);
	windows_.push_back(this);
}

