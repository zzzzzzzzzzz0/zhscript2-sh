/*
 * add.cpp
 *
 *  Created on: 2017年8月5日
 *      Author: zzzzzzzzzzz
 */

#include "add.h"
#include "window.h"
#include "pub/sig.h"
#include "pub/ext.h"
#include "pub/arg.h"

void add___::begin__(pub::view___ * view, void* w, bool from_view) {
	window___* window = (window___*)w;

	if(window) {
		if(from_view)
			if(!window->add__())
				window = new window___();
	} else
		window = new window___();

	add___* add = (add___*)window->add__();
	if(add)
		gtk_widget_set_name(view->widget__(), ("页" + std::to_string(++add->i_)).c_str());
	view->var__("", view);
	view->window_ = window;
}

static GtkNotebook *nb__(add___* add) {
	return GTK_NOTEBOOK(GTK_WIDGET(add->widget__()));
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

static pub::sigs___ sigs_ = {
		{"clicked", G_CALLBACK(cb_clicked__), "钮关闭", 'x'},
};

static void end_2__(pub::view___ * view, window___* window) {
	gtk_widget_grab_focus(view->widget__());
	gtk_widget_show_all(window->widget__());
}

void add___::end__(pub::view___ * view, bool to) {
	window___* window = (window___*)view->window_;
	add___* add = (add___*)window->add__();
	GtkWidget* scrolled = view->scrolled__();

	if(!add) {
		gtk_container_add (window->container__(), scrolled);
		end_2__(view, window);
	} else {
		switch(add->typ_) {
		case 'n': {
			GtkWidget *w = GTK_WIDGET(add->widget_);
			GtkNotebook *nb;
			if(!w) {
				w = gtk_notebook_new ();
				add->widget_ = w;
				nb = GTK_NOTEBOOK(w);
				switch(add->typ2_) {
				case 'l': gtk_notebook_set_tab_pos (nb, GTK_POS_LEFT); break;
				case 'r': gtk_notebook_set_tab_pos (nb, GTK_POS_RIGHT); break;
				case 'b': gtk_notebook_set_tab_pos (nb, GTK_POS_BOTTOM); break;
				}
				gtk_notebook_set_scrollable (nb, true);
				gtk_notebook_popup_enable (nb);
				gtk_container_add (window->container__(), w);
			} else
				nb = GTK_NOTEBOOK(w);
			GtkWidget *label = nullptr;
			if(add->has_button_) {
				GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
				view->var__("盒", box);
				GtkBox* box1 = GTK_BOX(box);
				label = gtk_label_new (nullptr);
				view->var__("标签", label);
				gtk_box_pack_start (box1, label, true, true, 0);
				if(add->can_close_) {
					GtkWidget *btn = gtk_button_new ();
					GtkButton* btn1 = GTK_BUTTON(btn);
					gtk_button_set_relief(btn1, GTK_RELIEF_NONE);
					gtk_button_set_image(btn1, gtk_image_new_from_icon_name("gtk-close", GTK_ICON_SIZE_MENU));
					gtk_box_pack_start (box1, btn, true, true, 0);
					sigs_.conn__(btn, view);
				}
				gtk_widget_show_all(box);
				label = box;
			}
			g_object_set_data(G_OBJECT(scrolled), "", view);
			gtk_notebook_append_page (nb, scrolled, label);

			end_2__(view, window);
			if(to) {
				int page_num = gtk_notebook_page_num(nb, scrolled);
				gtk_notebook_set_current_page (nb, page_num);
			}
			break;
		}}
	}
}

pub::view___* add___::get_view__(const char *name, void* w) {
	window___* window = (window___*)w;
	add___* add = (add___*)window->add__();
	pub::view___* ret = nullptr;
	if(!add) {
		GList *ls = gtk_container_get_children(window->container__());
		if(g_list_length (ls) > 0) {
			GtkWidget *w2 = GTK_WIDGET(ls->data);
			pub::view___* view = (pub::view___*)g_object_get_data(G_OBJECT(w2), "");
			if(view && (!name || !name[0] || name == std::string(view->name__())))
				ret = view;
		}
		g_list_free(ls);
	} else {
		switch(add->typ_) {
		case 'n': {
			GtkNotebook *nb = nb__(add);
			if(!name) {
				int page_num = gtk_notebook_get_current_page (nb);
				GtkWidget* scrolled = gtk_notebook_get_nth_page(nb, page_num);
				ret = (pub::view___*)g_object_get_data(G_OBJECT(scrolled), "");
			}
			break;
		}}
	}
	return ret;
}

void add___::close__(pub::view___ *view) {
	window___* window = (window___*)view->window_;
	add___* add = (add___*)window->add__();
	if(!add) {
		window->destroy__();
	} else {
		switch(add->typ_) {
		case 'n': {
			GtkNotebook *nb = nb__(add);
			int page_num = gtk_notebook_page_num(nb, view->scrolled__());
			gtk_notebook_remove_page(nb, page_num);
			if(gtk_notebook_get_n_pages(nb) == 0)
				window->destroy__();
			break; }
		}
	}
	sigs_.del__(nullptr, view);
	delete view;
}

add___* add___::mk__(char typ, char typ2, const std::vector<std::string>& p) {
	pub::arg___ canot_close {"不可关闭", -1},
				is_auto {"自动", -1};
	pub::args___ args {&canot_close, &is_auto};
	if(!args.parse__(p, 1))
		return nullptr;
	add___* add = new add___(typ, typ2);
	add->has_button_ = true;
	add->can_close_ = true;
	if(canot_close.a_.size() > 0) {
		add->has_button_ = true;
		add->can_close_ = false;
	}
	if(is_auto.a_.size() > 0) {
		add->has_button_ = false;
	}
	return add;
}

add___::~add___() {
	if(widget_) {
		switch(typ_) {
		case 'n':
			break;
		}
	}
}
