/*
 * liandong.cpp
 *
 *  Created on: 2017年8月10日
 *      Author: zzzzzzzzzzz
 */

#include "liandong.h"
#include <map>
#include <vector>
#include <functional>
#include "err.h"

#define int_no_ -10000

class liandong_pian___ {
public:
	int x_ = 0, y_ = 0;
	bool get_ = false;
	void get__(window___ *w, int x, int y);
};

class liandong_data___ {
public:
	std::string grpname_;
	int x_ = int_no_, y_ = int_no_;
	int x_by_move_ = int_no_, y_by_move_ = int_no_;
	bool is_min_ = false, is_max_ = false;

	bool w_is_max__(int w, int h);
	void no_no__(window___ *w2);
};

static std::map<window___ *, liandong_data___> map_;
static liandong_data___ *liandong_data__(window___ *w) {
	auto i = map_.find(w);
	return i == map_.end() ? nullptr : &i->second;
}

class liandong_data2___ {
public:
	std::vector<window___*> a_;
};

static std::map<std::string, liandong_data2___> grp_;

void liandong___::add__(window___ *w, const std::string &grpname) {
	liandong_data___ &dat = map_[w];
	dat.grpname_ = grpname;
	grp_[grpname].a_.push_back(w);
}

void liandong___::del__(window___ *w) {
	auto i = map_.find(w);
	if(i == map_.end())
		return;
	std::vector<window___*> &a = grp_[i->second.grpname_].a_;
	map_.erase(i);
	for(auto i2 = a.begin(); i2 != a.end(); i2++)
		if(*i2 == w) {
			a.erase(i2);
			break;
		}
}

static bool for_grp__(liandong_data___ *dat, window___ *w, std::function<void(liandong_data___ &,window___ *,bool&)> fn) {
	if(!dat) {
		dat = liandong_data__(w);
		if(!dat)
			return false;
	}
	for(auto i : grp_[dat->grpname_].a_) {
		auto i2 = map_.find(i);
		if(i2 == map_.end())
			continue;
		if(i == w)
			continue;
		bool b = false;
		fn(i2->second, i, b);
		if(b)
			return false;
	}
	return true;
}

void liandong___::window_destroy__(window___ *w) {
	for_grp__(nullptr, w, [&](liandong_data___ &, window___ *w2, bool&) {
		w2->destroy__();
	});
}

void liandong___::window_state__(window___ *w, unsigned state) {
	liandong_data___ *dat = liandong_data__(w);
	if(!dat)
		return;
#ifdef ver_debug_
	//debug_.o__("window_state__", w->name__(), ", ", state);
#endif
	if(state & GDK_WINDOW_STATE_ICONIFIED) {
		dat->is_min_ = true;
		for_grp__(dat, w, [&](liandong_data___ &, window___ *w2, bool&) {
			gtk_window_iconify(w2->hr__());
		});
	}
	if(dat->is_min_) {
		if(state & GDK_WINDOW_STATE_FOCUSED) {
			dat->is_min_ = false;
			for_grp__(dat, w, [&](liandong_data___ &, window___ *w2, bool&) {
				gtk_window_deiconify(w2->hr__());
			});
			gtk_window_present(w->hr__());
		}
	}
}

void liandong_pian___::get__(window___ *w, int x, int y) {
	int x2, y2;
	gtk_window_get_position(w->hr__(), &x2, &y2);
	x_ = x - x2;
	y_ = y - y2;
	get_ = true;
#ifdef ver_debug_
	debug_.o__("pian__ ", x_, ",", y_, "(", x, "-", x2, ",", y, "-", y2, ")");
#endif
}

static liandong_pian___ pian_;

void liandong_data___::no_no__(window___ *w2) {
	if(x_ == int_no_) {
		int x2, y2;
		gtk_window_get_position(w2->hr__(), &x2, &y2);
		x_ = x2 - pian_.x_;
		y_ = y2 - pian_.y_;
#ifdef ver_debug_
		debug_.o__("dat_no_no__ ", w2->name__(), " ", x_, ",", y_);
#endif
	}
}

static void move__(liandong_data___ *dat, window___ *w) {
	for_grp__(dat, w, [&](liandong_data___ &dat2, window___ *w2, bool&) {
		if(gtk_window_is_maximized(w2->hr__()))
			return;
		dat2.x_by_move_ = dat2.x_;
		dat2.y_by_move_ = dat2.y_;
#ifdef ver_debug_
		debug_.o__("move__ ", w2->name__(), " ",
				dat2.x_ - pian_.x_, "(", dat2.x_, "-", pian_.x_, "),",
				dat2.y_ - pian_.y_, "(", dat2.y_, "-", pian_.y_, ")");
#endif
		gtk_window_move(w2->hr__(), dat2.x_ - pian_.x_, dat2.y_ - pian_.y_);
	});
}

static bool can__(liandong_data___ *dat, int xadd, int yadd) {
	bool can = true;
	for_grp__(dat, nullptr, [&](liandong_data___ &dat2, window___ *w2, bool& b) {
		if(gtk_window_is_maximized(w2->hr__()))
			return;
		int x = dat2.x_ + xadd, y = dat2.y_ + yadd;
		if(x < 0 || y < 0 || x >= gdk_screen_width() || y >= gdk_screen_height()) {
#ifdef ver_debug_
			debug_.o__("can__ false ", w2->name__(), " ",
					x, "<0>", gdk_screen_width(), ", ",
					y, "<0>", gdk_screen_height());
#endif
			can = false;
			b = true;
			return;
		}
	});
	return can;
}

bool liandong_data___::w_is_max__(int w, int h) {
	int w1 = x_ + w, h1 = y_ + h;
	bool b = (w1 >= gdk_screen_width() && h1 >= gdk_screen_height());
#ifdef ver_debug_
	debug_.o__("w_is_max__ ", w1, ">=", gdk_screen_width(), ", ", h1, ">=", gdk_screen_height(), " ", b);
#endif
	is_max_ = b;
	return b;
}

void liandong___::window_move__(window___ *w, int x, int y) {
	liandong_data___ *dat = liandong_data__(w);
	if(!dat)
		return;
#ifdef ver_debug_
	//debug_.o__("window_move__", w->name__(), ", ", x, ",", y);
#endif
	if(dat->is_max_)
		return;

	if(x == dat->x_by_move_ && y == dat->y_by_move_) {
		return;
	} else {
		dat->x_by_move_ = dat->y_by_move_ = int_no_;
	}

	if(dat->x_ == int_no_) {
		dat->x_ = x;
		dat->y_ = y;
	}
	int		xadd = x - dat->x_,
			yadd = y - dat->y_;
	if(xadd == 0 && yadd == 0)
		return;

	if(!can__(dat, xadd, yadd)) return;
	for_grp__(dat, nullptr, [&](liandong_data___ &dat2, window___ *w2, bool&) {
		dat2.no_no__(w2);
		dat2.x_ += xadd;
		dat2.y_ += yadd;
	});
	pian_.get__(w, x, y);
	move__(dat, w);
}

void liandong___::window_resize__(window___ *w, int w_new, int w_old, int h_new, int h_old) {
	liandong_data___ *dat = liandong_data__(w);
	if(!dat)
		return;
#ifdef ver_debug_
	debug_.o__("window_resize__", w->name__(), ", ", w_new, ",", w_old, ", ", h_new, ",", h_old);
#endif
	int wadd = w_new - w_old, hadd = h_new - h_old;
	if(dat->w_is_max__(w_new, h_new))
		return;
	if(!can__(dat, wadd, hadd))
		return;
	for_grp__(dat, w, [&](liandong_data___ &dat2, window___ *w2, bool&) {
		dat2.no_no__(w2);
		if(dat2.x_ > dat->x_  + w_old /*&& dat2.y_ >= dat->y_ && dat2.y_ < dat->y_  + h_old*/)
			dat2.x_ += wadd;
		if(dat2.y_ > dat->y_  + h_old /*&& dat2.x_ >= dat->x_ && dat2.x_ < dat->x_  + w_old*/)
			dat2.y_ += hadd;
	});
	if(!pian_.get_)
		pian_.get__(w, dat->x_, dat->y_);
	move__(dat, w);
}

