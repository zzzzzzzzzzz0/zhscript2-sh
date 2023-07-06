/*
 * eventget.cpp
 *
 *  Created on: 2019年2月15日
 *      Author: zzzzzzzzzzz
 */

#include "eventget.h"
#include "ext.h"

namespace pub {

static gboolean event_mouse__(GtkWidget *widget, GdkEventButton *event, gpointer data) {
	event___* e = (event___*)data;
	//ext_->jieshi23__(e->code_.c_str(), e->name_.c_str(), nullptr, "ldd", event->button, event->x, event->y);
	std::vector<std::string> p, ret;
	p.push_back(std::to_string(event->button));
	p.push_back(std::to_string(event->x));
	p.push_back(std::to_string(event->y));
	ext_->jieshi__(nullptr, (pub::view___*)base___::var__(widget, ""),
			e->code_.c_str(), e->name_.c_str(), nullptr, false, &p, nullptr, &ret);
	if(ret.size() == 1) {
		if(ret[0] == "y") return true;
		if(ret[0] == "n") return false;
	}
	return e->b_;
}
static gboolean event_key__(GtkWidget *widget, GdkEventKey *event, gpointer data) {
	event___* e = (event___*)data;
	std::string state;
	if((event->state & GDK_SUPER_MASK))
		state += "Super";
	if((event->state & GDK_SHIFT_MASK))
		state += "Shift";
	if((event->state & GDK_CONTROL_MASK))
		state += "Control";
	if((event->state & GDK_MOD1_MASK))
		state += "Alt";
	//ext_->jieshi23__(e->code_.c_str(), e->name_.c_str(), nullptr, "ss", gdk_keyval_name(event->keyval), state.c_str());
	std::vector<std::string> p, ret;
	p.push_back(gdk_keyval_name(event->keyval));
	p.push_back(state);
	ext_->jieshi__(nullptr, nullptr, e->code_.c_str(), e->name_.c_str(), nullptr, false, &p, nullptr, &ret);
	if(!e->b_ && ret.size() == 1 && ret[0] == "x") {
		return TRUE;
	}
	return e->b_;
}
static gboolean event_scroll__(GtkWidget *widget, GdkEventScroll *scroll, gpointer data) {
	event___* e = (event___*)data;
	ext_->jieshi23__(e->code_.c_str(), e->name_.c_str(), nullptr, "l", scroll->direction);
	return e->b_;
}
static gboolean event_other__(GtkWidget *widget, GdkEvent *event, gpointer data) {
	event___* e = (event___*)data;
	ext_->jieshi23__(e->code_.c_str(), e->name_.c_str());
	return e->b_;
}


char event_get___::api__(const std::vector<std::string>& p, GObject *obj, size_t from, bool b) {
	for(size_t i2 = from; i2 < p.size();) {
		const std::string& p2 = p[i2++];
		if(i2 >= p.size()) {
			return '<';
		}
		const std::string& p3 = p[i2++];
		event___* e = new event___();
		e->code_ = p3;
		e->name_ = p2;
		e->b_ = b;
		std::string head = "key";
		if(p2.compare(0, head.size(), head) == 0) {
			g_signal_connect(obj, p2.c_str(), G_CALLBACK(event_key__), e);
			continue;
		}
		head = "button";
		if(p2.compare(0, head.size(), head) == 0 || p2 == "motion-notify-event") {
			g_signal_connect(obj, p2.c_str(), G_CALLBACK(event_mouse__), e);
			continue;
		}
		if(p2 == "scroll-event") {
			g_signal_connect(obj, p2.c_str(), G_CALLBACK(event_scroll__), e);
			continue;
		}
		if(p2 == "configure-event") {
			e->b_ = FALSE;
		}
		g_signal_connect(obj, p2.c_str(), G_CALLBACK(event_other__), e);
	}
	return 0;
}

event_get___::event_get___() {
}

event_get___::~event_get___() {
}

} /* namespace pub */
