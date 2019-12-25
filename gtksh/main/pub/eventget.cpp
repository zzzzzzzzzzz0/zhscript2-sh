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
	ext_->jieshi23__(e->code_.c_str(), e->name_.c_str(), nullptr, "ldd", event->button, event->x, event->y);
	return e->b_;
}
static gboolean event_key__(GtkWidget *widget, GdkEventKey *event, gpointer data) {
	event___* e = (event___*)data;
	ext_->jieshi23__(e->code_.c_str(), e->name_.c_str(), nullptr, "s", gdk_keyval_name(event->keyval));
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


char event_get___::api__(const std::vector<std::string>& p, GObject *obj) {
	for(size_t i2 = 1; i2 < p.size();) {
		const std::string& p2 = p[i2++];
		if(i2 >= p.size()) {
			return '<';
		}
		const std::string& p3 = p[i2++];
		event___* e = new event___();
		e->code_ = p3;
		e->name_ = p2;
		e->b_ = TRUE;
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
