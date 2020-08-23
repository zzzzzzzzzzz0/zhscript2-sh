/*
 * add.cpp
 *
 *  Created on: 2017年8月5日
 *      Author: zzzzzzzzzzz
 */

#include "add.h"
#include "window.h"
#include "area.h"
#include "pub/sig.h"
#include "pub/ext.h"
#include "pub/tag.h"
#include "err.h"
#include "pub/util.h"
#include "util.h"

void* add___::new_window__(pub::add_opt___* opt, bool is_main) {
	window___* window = new window___(opt->is_app_paintable_, is_main);
	if(!opt->window_name_.empty()) {
		window->name__(opt->window_name_.c_str());
		window->only_ = true;
	}
	return window;
}

unsigned long add_id_i_ = 0;
bool add___::begin__(pub::view___ * view, void* w, pub::view___ *from_view, pub::add_opt___* opt) {
	window___* window = (window___*)w;

	if(window) {
		//if(from_view) {
			if(opt->new_window_) {
				window = (window___*)new_window__(opt);
			}
		//}
	} else
		window = (window___*)new_window__(opt);

	bool is_new = false;
	area___ * area = area___::get__(window, opt->pos_, &is_new);
	if(is_new)
		area->opt_.copy__(opt);

	if(view) {
		if(opt->id_) {
			switch(area->opt_.typ_) {
			case 'n': {
				GtkNotebook *nb = area->nb__();
				for(int i = 0; i < gtk_notebook_get_n_pages(nb); i++) {
					pub::view___* v = area___::view__(nb, i);
					if(v->id_ == opt->id_) {
						gtk_notebook_set_current_page (nb, i);
						return false;
					}
				}
				break; }
			default:
				for(auto i : area->widget_) {
					if(area___::view__(i)->id_ == opt->id_)
						return false;
				}
				break;
			}
			view->id_ = opt->id_;
		} else
			view->id_ = ++add_id_i_;

		bool only = !opt->name_.empty();
		view->name__(only ? opt->name_.c_str() : ("页" + std::to_string(++((add___*)window->add__())->i_)).c_str());
		view->only_ = only;

		view->area_ = area;
		view->var__("", view);
		view->window_ = window;
	}
	if(from_view) {
		if(opt->from_) {
			view->from_ = opt->from_;
			tofrom__(view, true);
		} else {
			view->from_ = from_view->id_;
		}
	}

	if(opt->is_set_typ_) {
		pub::add_opt___* opt2 = &area->opt_;
		opt2->typ_ = opt->typ_;
		opt2->typ2_ = opt->typ2_;
	}
	if(!opt->code_.empty())
		area->opt_.code_ = opt->code_;
	return true;
}

static void cb_clicked__(GtkButton *button, gpointer user_data) {
	pub::sign___* sign = (pub::sign___*)user_data;
	pub::sig___* sig = sign->sig_;
	pub::view___ * view = (pub::view___ *)sign->data_;
	pub::ext_->jieshi2__(view, sig->name_);
	switch(sig->flag_) {
	case 'x': {
		sig->disconn__(button);
		add___::close__(view);
		break; }
	}
}

static pub::view___ *switch_page_ = nullptr;
static void switch_page__(GtkNotebook *notebook, gpointer *page,gint page_num){
	pub::view___ * view = area___::view__(notebook, page_num);
	if(switch_page_ != view)
		switch_page_ = view;
	else return;
	view->init2__(2);
	pub::ext_->jieshi2__(view, "页切换", "#", view);
}

static bool jieshi_drag_data__(char* uri, pub::view___* view, pub::plugin___* pi, pub::sig___* sig,
		GdkDragContext *context, GtkSelectionData *data, guint time) {
	std::vector<std::string> p, ret;
	p.push_back(pi->name_);
	p.push_back(uri);
	if(pub::ext_->jieshi__(nullptr, view, nullptr, sig->name_, nullptr, false, &p, nullptr, &ret)) {
		if(ret.size() == 1) {
			const std::string& s = ret[0];
			char* s2 = new char[s.length() + 1];
			s.copy(s2, s.length());
			s2[s.length()] = 0;
			gtk_selection_data_set_text (data, s2, s.length());
			gtk_drag_finish(context,TRUE,TRUE,time);
			return true;
		}
	}
	return false;
}
static void cb_drag_data_received__(GtkWidget *widget,
		GdkDragContext *context,
		gint x,gint y,
		GtkSelectionData *data,
		guint info,
		guint time,
		gpointer user_data)
{
	pub::sign___* sign = (pub::sign___*)user_data;
	pub::sig___* sig = (pub::sig___*)sign->sig_;
	pub::view___* view = (pub::view___*)sign->data_;
	pub::plugin___* pi = (pub::plugin___*)view->var__("插件");
#ifdef ver_debug_
	debug_.o__("cb_drag_data_received__ ",pi->name_," ",view->name__());
#endif
	if(pi->break_drag__()) {
		return;
	}
	GdkAtom atom=gtk_selection_data_get_data_type(data);
	if(gtk_targets_include_uri(&atom,1)) {
	} else {
		gchar *uris = (gchar *)gtk_selection_data_get_text (data);
		if(uris) {
			jieshi_drag_data__(uris, view, pi, sig, context, data, time);
			g_free (uris);
		}
	}
}

static pub::sigs___ sigs_btn_ = {
		{"clicked", G_CALLBACK(cb_clicked__), "钮关闭", 'x'},
}, sigs_view_ = {
		{"drag-data-received", G_CALLBACK(cb_drag_data_received__), "拖放"},
}, sigs_nb_ = {
		{"switch-page", G_CALLBACK(switch_page__)},
};

static void end_2__(pub::view___ * view, pub::add_opt___* opt, window___* window) {
	if(view) {
		if(opt->no_focus_)
			gtk_widget_set_can_focus(view->widget__(), false);
		else
			gtk_widget_grab_focus(view->widget__());
	}
	gtk_widget_show_all(window->widget__());
}

void add___::pack__(GtkWidget *w, pub::area___ * area, pub::add_opt___* opt) {
	char pos = area->opt_.pos_;
	if(opt->is_set_pos_)
		pos = opt->pos_;
	GtkWidget *box;
	switch(pos) {
	case 't': case 'T': box = box_; break;
	case 'b': case 'B': box = box4_; break;
	case 'l': case 'L': box = box2_; break;
	case 'r': case 'R': box = box3_; break;
	default: box = box1_; break;
	}
	((area___ *)area)->pack__(box, pos, opt, w);
}

void add___::end_1__(pub::view___ * view, pub::add_opt___* opt) {
	window___* window = (window___*)view->window_;
	GtkWidget* scrolled = view->scrolled__();
	area___ * area = (area___ *)view->area_;

	if(!box_) {
		GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
		gtk_container_add (window->container__(), box);
		box_ = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
		gtk_box_pack_start(GTK_BOX(box),box_,false,false,0);
		box4_ = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
		gtk_box_pack_end(GTK_BOX(box),box4_,false,false,0);
		GtkWidget* box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
		gtk_box_pack_end(GTK_BOX(box),box2,true,true,0);
		box2_ = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
		gtk_box_pack_start(GTK_BOX(box2),box2_,false,false,0);
		box3_ = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
		gtk_box_pack_end(GTK_BOX(box2),box3_,false,false,0);
		box1_ = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
		gtk_box_pack_end(GTK_BOX(box2),box1_,true,true,0);
	}
	switch(area->opt_.typ_) {
	default:
		area->widget_.push_back(view->widget__());
		pack__(scrolled, area, opt);
		sigs_view_.conn__(view->widget__(), view);
		end_2__(view, opt, window);
		break;
	case 'n': {
		GtkWidget *w = nullptr;
		if(area->widget_.size())
			w = GTK_WIDGET(area->widget_[0]);
		GtkNotebook *nb;
		if(!w) {
			w = gtk_notebook_new ();
			area->widget_.push_back((void*)w);
			nb = GTK_NOTEBOOK(w);
			switch(area->opt_.typ2_) {
			case 'l': gtk_notebook_set_tab_pos (nb, GTK_POS_LEFT); break;
			case 'r': gtk_notebook_set_tab_pos (nb, GTK_POS_RIGHT); break;
			case 'b': gtk_notebook_set_tab_pos (nb, GTK_POS_BOTTOM); break;
			}
			gtk_notebook_set_scrollable (nb, true);
			gtk_notebook_popup_enable (nb);
			sigs_nb_.conn__(nb);
			pack__(w, area, opt);
		} else
			nb = GTK_NOTEBOOK(w);
		GtkWidget *label = nullptr;
		bool can_close = false;
		bool has_button = area->opt_.has_button_;
		if(opt->is_set_has_button_)
			has_button = opt->has_button_;
		if(has_button) {
			GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
			view->var__("盒", box);
			gtk_widget_set_can_focus(box, false);
			GtkBox* box1 = GTK_BOX(box);
			label = gtk_label_new (nullptr);
			//gtk_widget_set_can_focus(label, false);
			view->var__("标签前", label);
			gtk_box_pack_start(box1,label,false,false,0);
			label = gtk_label_new (nullptr);
			//gtk_widget_set_can_focus(label, false);
			view->var__("标签", label);
			gtk_box_pack_start (box1, label, true, false, 0);
			can_close = area->opt_.can_close_;
			if(opt->is_set_can_close_)
				can_close = opt->can_close_;
			if(can_close) {
				GtkWidget *btn = gtk_button_new ();
				//gtk_widget_set_can_focus(btn, false);
				GtkButton* btn1 = GTK_BUTTON(btn);
				gtk_button_set_relief(btn1, GTK_RELIEF_NONE);
				gtk_button_set_image(btn1, gtk_image_new_from_icon_name("gtk-close", GTK_ICON_SIZE_MENU));
				gtk_box_pack_start (box1, btn, false, false, 0);
				sigs_btn_.conn__(btn, view);
				//gtk_widget_show(btn);
			}
			gtk_widget_show_all(box);
			//gtk_widget_show(box);
			label = box;
		}
		{
			sigs_view_.conn__(view->widget__(), view);
		}
		view->var__("-可关闭", (void*)can_close);
		g_object_set_data(G_OBJECT(scrolled), "", view);
		for(;;) {
			if(opt->append_ || area->opt_.append_) {
			} else {
				int page_num = gtk_notebook_get_current_page (nb);
				if(page_num >= 0) {
					view->from2_ = area___::view__(nb, page_num);
					if(opt->insert0_ || area->opt_.insert0_) {
					} else
						page_num++;
					gtk_notebook_insert_page (nb, scrolled, label, page_num);
					break;
				}
			}
			gtk_notebook_append_page (nb, scrolled, label);
			break;
		}
		gtk_notebook_set_tab_reorderable (nb, scrolled, true);
		end_2__(view, opt, window);

		bool to = area->opt_.to_;
		if(opt->is_set_to_)
			to = opt->to_;
		if(to) {
			int page_num = gtk_notebook_page_num(nb, scrolled);
			gtk_notebook_set_current_page (nb, page_num);
			view->var__("to", (void*)1);
		}
		break; }
	}
}

void add___::end_3__(pub::view___ * view, std::vector<std::string>* p, bool is_switch) {
	view->add_end__(*p);
	code__(view);
	view->add_end__(is_switch);
}

void add___::end__(pub::view___ * view, void* w, pub::add_opt___* opt, std::vector<std::string>* p, pub::plugin___ *p2) {
	window___* window = (window___*)w;
	if(!window)
		window = (window___*)view->window_;
	if(view) {
		add___* add = (add___*)window->add__();
		view->var__("插件", p2);
		add->end_1__(view, opt);
		end_3__(view, p, false);
	} else
		end_2__(nullptr, nullptr, window);
}

void add___::code__(pub::view___ * view) {
	if(view->from2_) {
		code__(view, 2, view->from2_);
		return;
	}
	code__(view, 1);
}
void add___::code__(pub::view___ * view, int i, pub::view___ * view2) {
	area___* area = (area___*)view->area_;
	if(area->opt_.code_.empty()) return;
	std::vector<std::string> p;
	char typ[3] = {area->opt_.typ_, area->opt_.typ2_, 0};
	p.push_back(typ);
	p.push_back(std::to_string(i));
	pub::ext_->push__(view, "#", p);
	if(view2)
		pub::ext_->push__(view2, "#", p);
	pub::ext_->jieshi__(nullptr, view, area->opt_.code_.c_str(), nullptr, nullptr, false, &p, nullptr, nullptr);
}

pub::view___* add___::get_view__(const char *name, void* w) {
	pub::view___* ret = nullptr;
	area___::view__(name, (window___*)w, [&](pub::view___* view) {
		ret = view;
	}, [&](pub::view___* view, int i, GtkNotebook *nb) {
		ret = view;
	});
	return ret;
}

void add___::for_view__(void* w, std::function<bool(pub::view___*)> fn) {
	area___::for__((window___*)w, [&](area___* area) {
		switch(area->opt_.typ_) {
		default: {
			for(auto i : area->widget_) {
				pub::view___* v = area___::view__(i);
				if(v && !fn(v))
					return true;
			}
			break; }
		case 'n': {
			GtkNotebook *nb = area->nb__();
			for(int i = 0; i < gtk_notebook_get_n_pages(nb); i++) {
				if(!fn(area___::view__(nb, i)))
					return true;
			}
			break; }
		}
		return false;
	});
}

bool add___::tofrom__(pub::view___ *view, bool b) {
	area___* area = (area___*)view->area_;
	switch(area->opt_.typ_) {
	case 'n': {
		GtkNotebook *nb = area->nb__();
		if(!b) {
			int i1 = gtk_notebook_page_num(nb, view->scrolled__());
			int i2 = gtk_notebook_get_current_page (nb);
			b = i1 == i2;
		}
		if(view->from_ && b) {
			for(int i = 0; i < gtk_notebook_get_n_pages(nb); i++) {
				pub::view___* v = area___::view__(nb, i);
				if(v->id_ == view->from_) {
					gtk_notebook_set_current_page (nb, i);
					return true;
				}
			}
		}
		break; }
	}
	return false;
}

void add___::close__(pub::view___ *view) {
	code__(view, 0);
	tofrom__(view, false);
	window___* window = (window___*)view->window_;
	area___* area = (area___*)view->area_;
	switch(area->opt_.typ_) {
	case 'n': {
		GtkNotebook *nb = area->nb__();
		gtk_notebook_remove_page(nb, gtk_notebook_page_num(nb, view->scrolled__()));
		for(int i = 0; i < gtk_notebook_get_n_pages(nb); i++) {
			pub::view___* v = area___::view__(nb, i);
			if(v->from2_ == view)
				v->from2_ = nullptr;
		}
		break; }
	}
	bool can_window_destroy = true;
	if(area->opt_.can_close_) {
		area___::for__(window, [&](area___* area2) {
			if(area2->opt_.first_no_) {
				can_window_destroy = false;
				return true;
			}
			switch(area2->opt_.typ_) {
			case 'n': {
				GtkNotebook *nb = area2->nb__();
				for(int i = 0; i < gtk_notebook_get_n_pages(nb); i++) {
					pub::view___* v = area___::view__(nb, i);
					if(v->var__("-可关闭")) {
						can_window_destroy = false;
						break;
					} else {
						if(area2->opt_.can_close_) {
							can_window_destroy = false;
							break;
						}
					}
				}
				break; }
			}
			return can_window_destroy ? false : true;
		});
	} else {
		can_window_destroy = false;
	}
	if(can_window_destroy)
		window->destroy__();
	sigs_btn_.del__(nullptr, view);
	delete view;
}

pub::view___* add___::activa__(const std::string &name, bool to) {
	window___ *w = nullptr;
	pub::view___* v = nullptr;
	std::string tname;
	if(util___::for_name__(name, w, tname)) {
		area___::view__(tname.c_str(), w, [&](pub::view___* view) {
			v = view;
		}, [&](pub::view___* view, int i, GtkNotebook *nb) {
			gtk_notebook_set_current_page (nb, i);
			v = view;
		});
	}
	if(v && to) {
		gtk_window_present(w->hr__());
		gtk_widget_grab_focus(v->widget__());
	}
	return v;
}

static pub::tags___ tags_ = {
		{"标签", "L", 0},
		{"标签前", "L2", 0},
		{"页关闭", "x", 0},
		{"页关闭所有", "X", 0},
		{"激活", "a", 1},
		{"设", "S", 0},
		{"无标签", "t", 0},
		{"无边框", "b", 0},
};

bool add___::api__(pub::view___ * view, void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret) {
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y': {
		area___* area = (area___*)view->area_;
		switch(tag[0]) {
		case 't':
		case 'b':
			switch(area->opt_.typ_) {
			case 'n':
				break;
			default:
				err_.buzhichi__(p);
				return true;
			}
			break;
		}
		switch(tag[0]) {
		case 'L': {
			void *v = view->var__(p[0].c_str());
			if(!v) {
				err_.wufa__(p, SIZE_MAX);
				return true;
			}
			GtkLabel *l = GTK_LABEL(v);
			if(p.size() > 1) {
				const std::string &s = p[1];
				gtk_label_set_markup(l, s.c_str());

				/*GtkWidget *w = GTK_WIDGET(v);
				if(s.empty())
					gtk_widget_hide(w);
				else
					gtk_widget_show(w);*/

				if(!tag[1]) {
					GtkWidget *w2 = view->/*widget*/scrolled__();
					GtkWidget *w = gtk_notebook_get_menu_label (area->nb__(), w2);
					if(!w) {
						w = gtk_label_new ("");
						gtk_widget_set_halign (w, GTK_ALIGN_START);
						gtk_notebook_set_menu_label (area->nb__(), w2, w);
					}
					l = GTK_LABEL(w);
					gtk_label_set_markup(l, s.c_str());
				}
			} else
				ret.push_back(gtk_label_get_text(l));
			break; }
		case 'X':
			switch(area->opt_.typ_) {
			case 'n': {
				GtkNotebook *nb = area->nb__();
				for(; gtk_notebook_get_n_pages(nb) > 0;)
					close__(area___::view__(nb, 0));
				return true; }
			}
			break;
		case 'x': close__(view); break;
		case 'a': {
			std::string name = p[1];
			if(name[0] == '#')
				name = ((window___*)view->window_)->name__() + name;
			activa__(name, true);
			break; }
		case 'S':
			if(!mk__(p, 1, p2))
				return true;
			break;
		case 't': gtk_notebook_set_show_tabs  (area->nb__(), !pub::bool__(p, 1, true)); break;
		case 'b': gtk_notebook_set_show_border(area->nb__(), !pub::bool__(p, 1, true)); break;
		}
		return true; }
	case '<':
		err_.buzu__(p);
		return true;
	}
	return false;
}

bool add___::mk__(const std::vector<std::string>& p, size_t from, std::vector<pub::data___>* p2) {
	pub::add_opt___ *opt = nullptr;
	if(p2) {
		for(auto d : *p2) {
			if(d.tag_[0] == 'o') {
				opt = (pub::add_opt___*)d.p_;
				break;
			}
		}
	}
	if(opt && area___::mk__(p, from, opt, nullptr))
		return true;
	err_.buzhichi__(p);
	return false;
}

void add___::del__(void* w) {
	window___* window = (window___*)w;
	area___::for__(window, [&](area___* area) {
		switch(area->opt_.typ_) {
		case 'n': {
			GtkNotebook *nb = area->nb__();
			sigs_nb_.del__(nb, nullptr);
			for(int i = 0; i < gtk_notebook_get_n_pages(nb); i++) {
				pub::view___* v = area___::view__(nb, i);
				sigs_btn_.del__(nullptr, v);
				sigs_view_.del__(v->widget__(), v);
			}
			break; }
		}
		delete area;
		return false;
	});
}
