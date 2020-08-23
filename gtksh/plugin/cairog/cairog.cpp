/*
 * cairog.cpp
 *
 *  Created on: 2018年01月21日
 *      Author: zzzzzzzzzzz
 */

#include "cairog.h"
#include "view.h"
#include "pub/tag.h"
#include "pub/ext.h"
#include "pub/util.h"
#include "gifsurface.h"
#include <cmath>

static std::vector<cairo_surface_t *> imgs_;

static std::vector<gif_surface___ *> gifs_;
static guint gif_timeout_ = 0;
static gboolean gif_timeout_cb__(gpointer data) {
	for(gif_surface___ *g : gifs_) {
		if(!g->auto_)
			continue;
		if(g->is_end__()) {
			if(!g->end_code_.empty()) {
				if(!pub::ext_->jieshi23__(g->end_code_.c_str()))
					continue;
				continue;
			}
		}
		if(g->next__()) {
			if(!g->next_code_.empty()) {
				if(!pub::ext_->jieshi23__(g->next_code_.c_str()))
					continue;
			}
			g->redraw__();
		}
	}
	return true;
}

static pub::tags___ tags_ = {
		{"夹角", "j", 4},
		{"距离", "d", 4},
		{"补间", "m", 6},
		{"像面", "sp", 1},
		{"动画面", "sg", 1},
};

bool cairog___::api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret) {
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y':
		switch(tag[0]) {
		case 'j': case 'd': {
			int x1 = std::stoi(p[1]),
				y1 = std::stoi(p[2]),
				x2 = std::stoi(p[3]),
				y2 = std::stoi(p[4]);
			int x = x2 - x1, y = y2 - y1;
			float f;
			switch(tag[0]) {
			case 'j':
				f = atan2(y, x) * 180 / M_PI;
				if(f > 0) f = f - 360;
				break;
			case 'd':
				f = sqrt(x*x + y*y);
				break;
			}
			char buf[16];
			sprintf(buf, "%.0f", f);
			ret.push_back(buf);
			break; }
		case 'm': {
			int x1 = std::stoi(p[1]),
				y1 = std::stoi(p[2]),
				x2 = std::stoi(p[3]),
				y2 = std::stoi(p[4]),
				end = std::stoi(p[5]),
				i = std::stoi(p[6]);
			int x, y;
			if(i <= 0) {
				x = x1;
				y = y1;
			} else if(i >= end) {
				x = x2;
				y = y2;
			} else {
				/*if(x1 == x2) {
					x = x1;
					y = (int)((double)(y2 - y1) / end * i) + y1;
				} else {
					double d = x2 - x1;
					x = (int)(d / end * i) + x1;
					y = (int)((x - x1) * (y2 - y1) / d + y1);
				}*/
				x = (int)((double)(x2 - x1) / end * i) + x1;
				y = (int)((double)(y2 - y1) / end * i) + y1;
			}
			ret.push_back(std::to_string(x));
			ret.push_back(std::to_string(y));
			break; }
		case 's':
			switch(tag[1]) {
			case 'p': {
				cairo_surface_t *img;
				if(p.size() == 2)
					img = cairo_image_surface_create_from_png(p[1].c_str());
				else
					img = (cairo_surface_t *)pub::stoul__(p[1]);
				if(!img) {
					pub::ext_->buzhichi__(p, 1);
					return true;
				}
				if(p.size() == 2) {
					imgs_.push_back(img);
					ret.push_back(std::to_string((long)img));
				} else {
					const std::string& opt = p[2];
					     if(opt == "宽") ret.push_back(std::to_string(cairo_image_surface_get_width(img)));
					else if(opt == "高") ret.push_back(std::to_string(cairo_image_surface_get_height(img)));
					else return false;
				}
				break; }
			case 'g': {
				gif_surface___ *g;
				if(p.size() == 2)
					g = gif_surface___::new__(p[1].c_str());
				else
					g = (gif_surface___ *)pub::stoul__(p[1]);
				if(!g) {
					pub::ext_->buzhichi__(p, 1);
					return true;
				}
				if(p.size() == 2) {
					gifs_.push_back(g);
					if(!gif_timeout_) {
						gif_timeout_ = g_timeout_add(100, gif_timeout_cb__, NULL);
					}
					ret.push_back(std::to_string((long)g));
				} else {
					const std::string& opt = p[2];
					     if(opt == "宽") ret.push_back(std::to_string(g->width__()));
					else if(opt == "高") ret.push_back(std::to_string(g->height__()));
					else if(opt == "间隔") ret.push_back(std::to_string(g->delay_time__()));
					else return false;
				}
				break; }
			}
			break;
		}
		return true;
	case '<':
		pub::ext_->buzu__(p, SIZE_MAX);
		return true;
	}
	return pub::plugin___::api__(shangji, p, p2, ret);
}

pub::view___* cairog___::new_view__() {
	return new view___();
}

cairog___::cairog___() {
}

cairog___::~cairog___() {
	for(cairo_surface_t *img : imgs_)
		cairo_surface_destroy(img);
	for(gif_surface___ *i : gifs_)
		delete i;
}

static cairog___ plugin_;
extern "C" void *plugin__(const std::string &path, const std::string &l4_so) {return &plugin_;}
