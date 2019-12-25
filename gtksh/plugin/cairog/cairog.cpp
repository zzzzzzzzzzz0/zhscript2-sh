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

static std::vector<cairo_surface_t *> imgs_;

static std::vector<gif_surface___ *> gifs_;

static pub::tags___ tags_ = {
		{"像面", "sp", 1},
		{"动画面", "sg", 1},
};

bool cairog___::api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret) {
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y':
		switch(tag[0]) {
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
