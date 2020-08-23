/*
 * view.cpp
 *
 *  Created on: 2018年01月21日
 *      Author: zzzzzzzzzzz
 */

#include "view.h"
#include "pub/sig.h"
#include "pub/tag.h"
#include "pub/ext.h"
#include "pub/util.h"
#include "pub/plugin.h"
#include "cairog.h"
#include "gifsurface.h"
#ifdef ver_debug_
#include <iostream>
#endif
#include <cmath>

static cairog___ *plugin_ = nullptr;

static pub::tags___ tags_callback_ = {
		{"颜色", "c", 4},
		{"涂绘", "p", 0},
		{"缩放", "S", 2},
		{"原点", "T", 2},
		{"线宽", "w", 1},
		{"圆形线帽", "A", 0},
		{"移", "m", 2},
		{"旋转", "o", 1},
		{"直线", "l", 2},
		{"弧线", "a", 5},
		{"文字", "t", 1},
		{"文字大小", "ts", 1},
		{"文字字体", "tf", 1},
		{"描画", "s", 0},
		{"描画二", "s2", 0},
		{"填充", "f", 0},
		{"填充二", "f2", 0},
		{"裁剪域", "C", 0},
		{"保存", "v", 0},
		{"恢复", "r", 0},
		{"sin", "3s", 1},
		{"cos", "3c", 1},
		{"像面", "R", 3},
		{"动画面", "G", 3},
		{"写文件", "W", 1},
};

static void callback__(view___* view, cairo_t *cr, char *buf, int argc, ...) {
	if(!argc) return;
	auto x__ = [&] {
		buf[0] = 'x';
		buf[1] = 0;
		view->draw_code_ok_ = false;
	};
	auto d__ = [&](double d) {
		const std::string s = std::to_string(d);
		s.copy(buf, s.length());
		buf[s.length()] = 0;
	};
	std::vector<std::string> p;
	{
		va_list argv;
		va_start(argv, argc);
		for (int i = 0; i < argc; ++i) {
			char* s = va_arg(argv, char*);
			p.push_back(s ? s : null_);
		}
		va_end(argv);
	}
	size_t from = 0;
	auto stof = [&](size_t i) {return std::stod(p[i + from]);};
	auto stol = [&](size_t i) {return std::stol(p[i + from]);};
	auto cstr = [&](size_t i) {return p[i + from].c_str();};
	for(;;) {
		std::string tag;
		size_t argc2;
		switch(tags_callback_.get__(p, tag, &argc2, from)) {
		case 'y':
#ifdef ver_debug_
			/*for(size_t i = 0; i <= argc2; i++) {
				size_t i2 = i + from;
				std::cout << "(" << i2 << ")" << p[i2] << (i < argc2 ? ", " : "\n");
			}*/
#endif
			try {
				switch(tag[0]) {
				case 'c': cairo_set_source_rgba(cr, stof(1), stof(2), stof(3), stof(4)); break;
				case 'p': cairo_paint(cr); break;
				case 'm': cairo_move_to(cr, stof(1), stof(2)); break;
				case 'o': cairo_rotate(cr, stof(1)); break;
				case 'l': cairo_line_to(cr, stof(1), stof(2)); break;
				case 'a': cairo_arc(cr, stof(1), stof(2), stof(3), stof(4), stof(5)); break;
				case 's':
					switch(tag[1]) {
					default:  cairo_stroke(cr); break;
					case '2': cairo_stroke_preserve(cr); break;
					}
					break;
				case 't':
					switch(tag[1]) {
					case 's': cairo_set_font_size (cr, stof(1)); break;
					case 'f': cairo_select_font_face (cr, cstr(1), CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL); break;
					/*
					cairo_text_extents_t te;
					cairo_text_extents (cr, s, &te);
					cairo_move_to (cr, i + 0.5 - te.x_bearing - te.width / 2, 0.5 - te.y_bearing - te.height / 2);
					*/
					default: cairo_show_text (cr, cstr(1)); break;
					}
					break;
				case 'S': cairo_scale(cr, stof(1), stof(2)); break;
				case 'T': cairo_translate(cr, stof(1), stof(2)); break;
				case 'w': cairo_set_line_width(cr, stof(1)); break;
				case 'A': cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND); break;
				case 'f':
					switch(tag[1]) {
					default:  cairo_fill(cr); break;
					case '2': cairo_fill_preserve(cr); break;
					}
					break;
				case 'C': cairo_clip(cr); break;
				case 'v': cairo_save(cr); break;
				case 'r': cairo_restore(cr); break;
				case '3':
					switch(tag[1]) {
					case 's':
						d__(sin(stof(1)));
						break;
					case 'c':
						d__(cos(stof(1)));
						break;
					}
					break;
				case 'R':
					cairo_set_source_surface(cr, (cairo_surface_t *)stol(1), stof(2), stof(3));
					break;
				case 'G': {
					gif_surface___ *g = (gif_surface___ *)stol(1);
					g->win_ = gtk_widget_get_window(view->widget__());
					g->x_ = stof(2);
					g->y_ = stof(3);
					gdk_cairo_set_source_pixbuf(cr, g->pixbuf__(), g->x_, g->y_);
					break; }
				case 'W':
					cairo_surface_write_to_png (cairo_get_target (cr), cstr(1));
					break;
				}
			} catch(std::invalid_argument &ia) {
				pub::ext_->throw2__("数字格式错误 ", ia);
				x__();
				return;
			}
			if((from += argc2 + 1) < p.size())
				break;
			return;
		case '<':
			pub::ext_->throw_buzu__(p, SIZE_MAX);
			x__();
			return;
		default:
			pub::ext_->throw_buzhichi__(p, SIZE_MAX);
			x__();
			return;
		}
	}
}

static pub::tags___ tags_ = {
		{"刷新", "u", 0},
		{"动画面", "G", 2},
		{"蓝代码", " ", 0},
		{"列命令", "L", 1},
};

bool view___::api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret) {
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y':
		switch(tag[0]) {
		case 'u':
			gtk_widget_queue_draw (hr_);
			break;
		case 'G': {
			gif_surface___ *g = (gif_surface___ *)pub::stoul__(p[1]);
			if(g) {
				const std::string& opt = p[2];
				if(opt == "有更") {
					if(g->next__()) {
						g->redraw__();
					}
					break;
				}
				if(opt == "自动") {g->auto_ = true; break;}
				if(opt == "暂停") {g->auto_ = false; break;}
				if(opt == "下时") {
					if(p.size() > 3) {
						g->next_code_ = p[3];
						break;
					}
				}
				if(opt == "末时") {
					if(p.size() > 3) {
						g->end_code_ = p[3];
						break;
					}
				}
			}
			pub::ext_->buzhichi__(p, SIZE_MAX);
			return true; }
		case ' ':
			if(!draw_code__(p, 1))
				ret.push_back(draw_code_);
			break;
		case 'L': {
			std::string ret2;
			for(auto i : tags_callback_.a_) {
				std::vector<std::string> in, out;
				in.push_back(i.flag_);
				in.push_back(i.flag2_);
				in.push_back(std::to_string(i.argc_));
				pub::ext_->jieshi__(nullptr, this, p[1].c_str(), nullptr, shangji, false, &in, nullptr, &out);
				for(auto i2 : out)
					ret2 += i2;
			}
			ret.push_back(ret2);
			break; }
		}
		return true;
	case '<':
		pub::ext_->buzu__(p, SIZE_MAX);
		return true;
	}
	return pub::view___::api__(shangji, p, p2, ret);
}

bool view___::draw_code__(const std::vector<std::string>& p, size_t i) {
	if(p.size() > i) {
		draw_code_ = p[i];
		draw_code_ok_ = !draw_code_.empty();
		return true;
	}
	return false;
}

void view___::new_open__(const std::vector<std::string>& p) {
	//draw_code__(p, 0);
}

static gboolean cb_draw__(GtkWidget * widget, GdkEventExpose * event, gpointer data) {
	pub::sign___* sign = (pub::sign___*)data;
	view___* view = (view___*)sign->data_;
	if(view->draw_code_ok_) {
		cairo_t *cr = gdk_cairo_create(gtk_widget_get_window(widget));
		std::string code;
		code += "函数“口”以“&”、“" + std::to_string((unsigned long)callback__) + "”、“-${l" +
				std::to_string((long)view) + "}-${l" +
				std::to_string((long)cr) + "}-B-Z”。基于先";
#ifdef ver_debug_
		//code += "显示‘参数’换行。";
#endif
		code += "如果调用‘口’、‘参数栈’等于“x”那么退出“1”。了先" + view->draw_code_ + "了";
		bool ok = pub::ext_->jieshi23__(code.c_str());
		if(!ok)
			view->draw_code_ok_ = false;
		cairo_destroy(cr);
	}
	return FALSE;
}

static pub::sigs___ sigs_ = {
		{"draw", G_CALLBACK(cb_draw__)},
};

view___::view___() {
	hr_ = gtk_drawing_area_new ();

	sigs_.conn__(hr_, this);
}

view___::~view___() {
}

extern "C" void ext__(pub::ext___* ext, pub::plugin___ *plugin) {
	pub::ext_ = ext;
	plugin_ = (cairog___ *)plugin;
}
