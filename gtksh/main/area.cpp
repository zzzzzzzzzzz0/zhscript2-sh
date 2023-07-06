/*
 * area.cpp
 *
 *  Created on: 2017年12月11日
 *      Author: zzzzzzzzzzz
 */

#include "area.h"
#include "pub/arg.h"
#include "pub/util.h"

GtkNotebook *area___::nb__() {
	if(widget_.size())
		return GTK_NOTEBOOK(GTK_WIDGET(widget_[0]));
	return nullptr;
}

static GtkWidget *w__(GtkWidget *w) {
	return w;
}

static GtkWidget *sw__(GtkWidget *w, pub::add_opt___* opt) {
	GtkWidget *sw = gtk_scrolled_window_new (NULL, NULL);
	GtkScrolledWindow *sw1 = GTK_SCROLLED_WINDOW(sw);
	gtk_scrolled_window_set_policy (sw1, GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_container_add (GTK_CONTAINER (sw), w);
	gtk_widget_set_size_request (sw, opt->w_req_, opt->h_req_);
	/*if(opt->w_req_ >= 0)
		gtk_scrolled_window_set_min_content_width(sw1, opt->w_req_);
	if(opt->h_req_ >= 0)
		gtk_scrolled_window_set_min_content_height(sw1, opt->h_req_);*/
	return w__(sw);
}

void area___::pack__(GtkWidget *box, char pos, pub::add_opt___* opt, GtkWidget *w) {
	GtkBox *box2 = GTK_BOX(box);
	switch(pos) {
	case 't': case 'b': case 'l': case 'r':
		if(opt->w_req_ >= 0 || opt->h_req_ >= 0)
			gtk_box_pack_start(box2,sw__(w, opt),true,true,0);
		else
			gtk_box_pack_start(box2,w__(w),FALSE,FALSE,0);
		break;
	case 'T': case 'B': case 'L': case 'R':
		if(opt->w_req_ >= 0 || opt->h_req_ >= 0)
			gtk_box_pack_end(box2,sw__(w, opt),true,true,0);
		else
			gtk_box_pack_end(box2,w__(w),FALSE,FALSE,0);
		break;
	default:
		gtk_box_pack_end(box2,w__(w),true,true,0);
		break;
	}
}

area___ *area___::get__(window___* window, char pos, bool* is_new) {
	std::string name = "区域";
	name += pos;
	area___ *area = (area___ *)window->var__(name.c_str());
	if(!area && is_new) {
		area = new area___();
		window->var__(name.c_str(), area);
		*is_new = true;
	}
	return area;
}

void area___::for__(window___* window, std::function<bool(area___ *)> fn) {
	auto fn2 = [&](char pos) {
		area___ *area = get__(window, pos);
		if(area && fn(area))
			return true;
		return false;
	};
	if(fn2('c')) return;
	if(fn2('t')) return;
	if(fn2('T')) return;
	if(fn2('b')) return;
	if(fn2('B')) return;
	if(fn2('l')) return;
	if(fn2('L')) return;
	if(fn2('r')) return;
	if(fn2('R')) return;
}

bool area___::mk__(const std::vector<std::string>& p, size_t from, pub::add_opt___* opt, std::vector<std::string>* other) {
	auto typ = [&](const char* typ) {
		opt->typ_ = typ[0];
		opt->typ2_ = typ[1];
		opt->is_set_typ_ = true;
	};
	auto has_button = [&](bool b) {
		opt->has_button_ = b;
		opt->is_set_has_button_ = true;
	};
	auto can_close = [&](bool b) {
		opt->can_close_ = b;
		has_button(true);
		opt->is_set_can_close_ = true;
	};
	auto pos = [&](char c) {
		opt->pos_ = c;
		opt->is_set_pos_ = true;
	};
	pub::args___ args {
		{[&](pub::arg___*) {typ("n");}, {"-标签页", "-顶标签页"}},
		{[&](pub::arg___*) {typ("nb");}, {"-底标签页"}},
		{[&](pub::arg___*) {typ("nl");}, {"-左标签页"}},
		{[&](pub::arg___*) {typ("nr");}, {"-右标签页"}},
		{[&](pub::arg___*) {opt->new_window_ = true;}, {"-新窗"}},
		{[&](pub::arg___*) {opt->is_popup_ = true;}, {"-弹出窗"}},
		{[&](pub::arg___*) {opt->is_app_paintable_ = true;}, {"-自绘"}},
		{[&](pub::arg___*) {can_close(false);}, {"-不可关闭"}},
		{[&](pub::arg___*) {can_close(true);}, {"-可关闭"}},
		{[&](pub::arg___*) {has_button(false);}, {"-自动"}},
		{[&](pub::arg___*) {opt->to_ = false; opt->is_set_to_ = true;}, {"-不激活"}},
		{[&](pub::arg___*) {opt->to2_ = false;}, {"-再不激活"}},
		{[&](pub::arg___*) {pos('t');}, {"-上上"}},
		{[&](pub::arg___*) {pos('T');}, {"-上下"}},
		{[&](pub::arg___*) {pos('b');}, {"-下上"}},
		{[&](pub::arg___*) {pos('B');}, {"-下下"}},
		{[&](pub::arg___*) {pos('l');}, {"-左左"}},
		{[&](pub::arg___*) {pos('L');}, {"-左右"}},
		{[&](pub::arg___*) {pos('r');}, {"-右左"}},
		{[&](pub::arg___*) {pos('R');}, {"-右右"}},
		{[&](pub::arg___* t) {opt->w_req_ = pub::stoi__(p[t->i_]);}, {"-宽"}, 1},
		{[&](pub::arg___* t) {opt->h_req_ = pub::stoi__(p[t->i_]);}, {"-高"}, 1},
		{[&](pub::arg___* t) {opt->name_ = p[t->i_];}, {"-名"}, 1},
		{[&](pub::arg___* t) {opt->window_name_ = p[t->i_];}, {"-窗名"}, 1},
		{[&](pub::arg___* t) {opt->from_ = pub::stoul__(p[t->i_]);}, {"-从"}, 1},
		{[&](pub::arg___* t) {opt->id_   = pub::stoul__(p[t->i_]);}, {"-id"}, 1},
		{[&](pub::arg___* t) {opt->code_ = p[t->i_];}, {"-代码"}, 1},
		{[&](pub::arg___*) {opt->first_no_ = true;}, {"-空"}},
		{[&](pub::arg___*) {opt->down_ = true;}, {"-从"}},
		{[&](pub::arg___*) {opt->no_focus_ = true;}, {"-无焦点"}},
		{[&](pub::arg___*) {opt->append_ = true;}, {"-追加"}},
		{[&](pub::arg___*) {opt->insert0_ = true;}, {"-前插"}},
		{[&](pub::arg___*) {opt->left_ = true;}, {"-前固"}},
		{[&](pub::arg___*) {opt->use_open_ = false;}, {"-不默开"}},
		{[&](pub::arg___*) {opt->only_switch_ = true;}, {"-仅切换"}},
		{[&](pub::arg___*) {opt->to_ = false; opt->is_set_to_ = opt->no_switch_ = true;}, {"-不切换"}},
	};
	if(other) {
		args.a_.push_back({[&](pub::arg___* t) {
			other->push_back(p[t->i_]);
		}, {}, 1});
	}
	bool b = args.parse__(p, from) == 0;
	if(b) {
		switch(opt->pos_) {
		case 't':case 'T':case 'b':case 'B':
			if(opt->h_req_ == -1)
				opt->h_req_ = 60;
			break;
		case 'l':case 'L':case 'r':case 'R':
			if(opt->w_req_ == -1)
				opt->w_req_ = 200;
			break;
		}
	}
	return b;
}

pub::view___* area___::view__(void* widget) {
	return (pub::view___*)pub::base___::var__(GTK_WIDGET(widget), "");
}
pub::view___* area___::view__(GtkNotebook *nb, int page_num) {
	GtkWidget* scrolled = gtk_notebook_get_nth_page(nb, page_num);
	return view__(scrolled);
}
void area___::view__(const char *name, window___* window, std::function<void(pub::view___*)> fn,
		std::function<void(pub::view___*, int, GtkNotebook*)> fnn) {
	pub::view___* ret = nullptr;
	std::string name1;
	if(name && name[0])
		name1 = name;
	for__(window, [&](area___* area) {
		switch(area->opt_.typ_) {
		default:
			for(auto i : area->widget_) {
				pub::view___* view = view__(i);
				if(view && (name1.empty() || name1 == view->name__())) {
					ret = view;
					fn(ret);
				}
			}
			break;
		case 'n': {
			GtkNotebook *nb = area->nb__();
			if(nb) {
				if(name1.empty()) {
					int i = gtk_notebook_get_current_page (nb);
					if(i >= 0) {
						ret = view__(nb, i);
						fnn(ret, i, nb);
					}
				} else {
					for(int i = 0; i < gtk_notebook_get_n_pages(nb); i++) {
						pub::view___* view = view__(nb, i);
						if(name1 == view->name__()) {
							ret = view;
							fnn(ret, i, nb);
							break;
						}
					}
				}
			}
			break; }
		}
		return ret ? true : false;
	});
}
