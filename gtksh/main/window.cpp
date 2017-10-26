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
#include "liandong.h"
static liandong___ liandong_;

static pub::tags___ tags_ = {
		{"移动", "m", 0},
		{"标题", "t", 1},
		{"标签", "L", 0},
		{"图标", "i", 1},
		{"最大化", "A", 0},
		{"大小", "s", 0},
		{"窗名", "N", 0},
		{"置顶", "T", 0},
		{"取消置顶", "Tx", 0},
		{"置底", "B", 0},
		{"取消置底", "Bx", 0},
		{"关闭", "x", 0},
		{"无修饰", "d", 0},
		{"标签页", "n", 0},
		{"左标签页", "nl", 0},
		{"右标签页", "nr", 0},
		{"顶标签页", "n", 0},
		{"底标签页", "nb", 0},
		{"联动", "-", 1},
};

bool window___::api__(void* shangji, const std::vector<std::string>& p, std::vector<std::string>& ret) {
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y':
		switch(tag[0]) {
		case 'm':
			if(p.size() > 2)
				gtk_window_move(hr_, std::stoi(p[1]), std::stoi(p[2]));
			else {
				int x, y;
				gtk_window_get_position(hr_, &x, &y);
				ret.push_back(std::to_string(x));
				ret.push_back(std::to_string(y));
			}
			break;
		case 't':
			gtk_window_set_title(hr_, p[1].c_str());
			break;
		case 'L': {
			pub::view___* v = add___::get_view__(nullptr, this);
			if(!v) {
				err_.wufa__(p);
				return true;
			}
			GtkLabel *l = GTK_LABEL(v->var__(p[0].c_str()));
			if(!l) {
				err_.buzhichi__(p);
				return true;
			}
			if(p.size() > 1)
				gtk_label_set_markup(l, p[1].c_str());
			else
				ret.push_back(gtk_label_get_text(l));
			break; }
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
		case 'A':
			gtk_window_maximize (hr_);
			break;
		case 's':
			if(p.size() > 1) {
				int w = std::stoi(p[1]);
				gtk_window_resize(hr_, w, p.size() > 2 ? std::stoi(p[2]) : w);
			} else {
				gint w = 0, h = 0;
				gtk_window_get_size (hr_, &w, &h);
				//width_ height_
				ret.push_back(std::to_string(w));
				ret.push_back(std::to_string(h));
			}
			break;
		case 'N':
			ret.push_back(name__());
			break;
		case 'T':
			gtk_window_set_keep_above (hr_, tag[1] == 0);
			break;
		case 'B':
			gtk_window_set_keep_below (hr_, tag[1] == 0);
			break;
		case 'd':
			gtk_window_set_decorated(hr_, false);
			break;
		case 'x':
			this->destroy__();
			break;
		case 'n': {
			add___* add = (add___*)add_;
			if(add)
				delete add;
			add = add___::mk__('n', tag[1], p);
			if(!add) {
				err_.buzhichi__(p);
				return true;
			}
			add_ = add;
			break; }
		case '-':
			liandong_.add__(this, p[1]);
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
	//g_message("Destroying window.");
	pub::sign___* sign = (pub::sign___*)user_data;
	pub::sig___* sig = sign->sig_;
	sig->disconn__(widget);
	window___* w = (window___*)sign->data_;
	pub::ext_->jieshi3__(w, w->is_main__() ? sig->name_ : "关闭");
	if(w->is_main__())
		gtk_main_quit();
	liandong_.window_destroy__(w);
	//delete w;
}

static gboolean cb_configure_event__(GtkWidget *widget, GdkEventConfigure *event, gpointer user_data) {
	window___* win = (window___*)((pub::sign___*)user_data)->data_;
	int w = event->width, h = event->height;
	if(win->width_ != w || win->height_ != h) {
		switch(win->width_) {
		case -1:
			break;
		default: {
			GList *ls = gtk_container_get_children(win->container__());
			for (GList *i = ls; i; i = i->next) {
				GtkWidget *wid = GTK_WIDGET(i->data);
				gtk_widget_queue_resize (wid);
			}
			g_list_free(ls);
			liandong_.window_resize__(win, w, win->width_, h, win->height_);
			break; }
		}
		win->width_ = w;
		win->height_ = h;
	}
	liandong_.window_move__(win, event->x, event->y);
	return TRUE;
}

static gboolean cb_window_state_event__(GtkWidget *widget, GdkEventWindowState *event, gpointer user_data) {
	liandong_.window_state__((window___*)((pub::sign___*)user_data)->data_, event->new_window_state);
	return TRUE;
}

static pub::sigs___ sigs_ = {
		{"destroy", G_CALLBACK(cb_destroy__), "销毁"},
		{"configure_event", G_CALLBACK(cb_configure_event__)},
		{"window-state-event", G_CALLBACK(cb_window_state_event__)},
};

void window___::destroy__() {
	g_signal_emit_by_name(widget__(),"destroy");
}

std::vector<window___*> windows_;

window___::~window___() {
	sigs_.del__(hr_, this);
	liandong_.del__(this);
	if(add_)
		delete (add___*)add_;
	for(auto i = windows_.begin(); i != windows_.end(); i++)
		if(*i == this) {
			windows_.erase(i);
			break;
		}
}

static int i_ = 0;

window___::window___(bool is_main) : is_main_(is_main) {
	hr_ = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
	gtk_widget_set_name(widget__(), ("窗" + std::to_string(++i_)).c_str());
	sigs_.conn__(hr_, this);
	windows_.push_back(this);
}

