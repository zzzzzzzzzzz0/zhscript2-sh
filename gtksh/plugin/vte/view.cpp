/*
 * view.cpp
 *
 *  Created on: 2017年09月12日
 *      Author: zzzzzzzzzzz
 */

#include "view.h"
#include "pub/sig.h"
#include "pub/tag.h"
#include "pub/ext.h"
#include "pub/plugin.h"
#include "vte.h"

static vte___ *plugin_ = nullptr;

static pub::tags___ tags_ = {
		{"插入", "i", 1},
		{"命令", "c", 1},
};

bool view___::api__(void* shangji, const std::vector<std::string>& p, std::vector<std::string>& ret) {
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y':
		switch(tag[0]) {
		case 'i': {
			const std::string& data = p[1];
			vte_terminal_feed_child(hr__(), data.c_str(), data.length());
			break; }
		case 'c': {
			char **argv = NULL;
			g_shell_parse_argv(p[1].c_str(), NULL, &argv, NULL);
			char** envv = NULL;
			if(p.size() > 3) {
				g_shell_parse_argv(p[3].c_str(), NULL, &envv, NULL);
			}
			GError *error = NULL;
			//VTE_PTY_NO_LASTLOG|VTE_PTY_NO_UTMP|VTE_PTY_NO_WTMP
			VtePtyFlags pf = (VtePtyFlags)(0);
			//G_SPAWN_CHILD_INHERITS_STDIN|G_SPAWN_SEARCH_PATH|G_SPAWN_FILE_AND_ARGV_ZERO
			//G_SPAWN_SEARCH_PATH
			GSpawnFlags sf = (GSpawnFlags)(0);
			GPid pid = 0;
			vte_terminal_spawn_sync(hr__(),
					pf, p.size() > 2 ? p[2].c_str() : nullptr, argv, envv,
					sf, NULL, NULL, &pid, NULL, &error);
			g_error_free (error);
			ret.push_back(std::to_string(pid));
			break; }
		}
		return true;
	case '<':
		pub::ext_->buzu__(p);
		return true;
	}
	return pub::view___::api__(shangji, p, ret);
}

void view___::new_open__(const std::vector<std::string>& p) {
}

static void cb__(VteTerminal* vte, void* data_in) {
	pub::sign___* sign = (pub::sign___*)data_in;
	view___* view = (view___*)sign->data_;
	switch(sign->sig_->flag_) {
	case 'i':
		if(!view->init_) {
			view->init_ = true;
			pub::ext_->jieshi2__(view, "初始");
		}
		return;
	}
	pub::ext_->jieshi2__(view, sign->sig_->name_);
}
static void cb2__(VteTerminal* vte, int arg1, void* data_in) {
	pub::sign___* sign = (pub::sign___*)data_in;
	view___* view = (view___*)sign->data_;
	pub::ext_->jieshi2s__(view, sign->sig_->name_, std::to_string(arg1).c_str());
}

static pub::sigs___ sigs_ = {
		{"contents-changed", G_CALLBACK(cb__), "内容改变"},
		{"cursor-moved", G_CALLBACK(cb__), nullptr, 'i'},
		{"child-exited", G_CALLBACK(cb2__), "内退"},
};

view___::view___() {
	box_ = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_set_homogeneous(GTK_BOX(box_), FALSE);
	hr_ = vte_terminal_new();
	gtk_box_pack_start(GTK_BOX(box_), hr_, TRUE, TRUE, 0);
	GtkWidget *scrollbar = gtk_scrollbar_new(GTK_ORIENTATION_VERTICAL,
			gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(hr__())));
	gtk_box_pack_end(GTK_BOX(box_), scrollbar, FALSE, FALSE, 0);

	sigs_.conn__(hr_, this);
}

view___::~view___() {
	sigs_.del__(hr_, this);
}

extern "C" void ext__(pub::ext___* ext, pub::plugin___ *plugin) {
	pub::ext_ = ext;
	plugin_ = (vte___ *)plugin;
}
