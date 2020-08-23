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

#ifdef ver_debug_
#include "pub/debug.h"
pub::debug___ debug_;
#endif

static vte___ *plugin_ = nullptr;

static void cmd__(const std::vector<std::string>& p, size_t from, VteTerminal* hr, GPid* pid, std::vector<std::string>* ret) {
	GError *error = NULL;
	char **argv = NULL;
	int argc = 0;
	{
		std::string arg = p[from];
		if(plugin_->arg1_.find(arg) == 0)
			arg = plugin_->arg1_;
		g_shell_parse_argv(arg.c_str(), &argc, &argv, &error);
	}
	if(!error) {
		std::string env = plugin_->env1_;
		size_t i = from + 2;
		if(p.size() > i && !p[i].empty()) {
			if(!env.empty())
				env += "\n";
			env += p[i].c_str();
		}
		char** envv = NULL;
		if(!env.empty())
			g_shell_parse_argv(env.c_str(), NULL, &envv, &error);
		if(!error) {
			//VTE_PTY_NO_LASTLOG|VTE_PTY_NO_UTMP|VTE_PTY_NO_WTMP
			//(VtePtyFlags)(0)
			VtePtyFlags pf = VTE_PTY_DEFAULT;
			//G_SPAWN_CHILD_INHERITS_STDIN|G_SPAWN_SEARCH_PATH|G_SPAWN_FILE_AND_ARGV_ZERO
			//(GSpawnFlags)(0)
			GSpawnFlags sf = G_SPAWN_SEARCH_PATH;
			i = from + 1;
			vte_terminal_spawn_sync(hr, pf,
				p.size() > i && !p[i].empty() ? p[i].c_str() : nullptr, argv, envv,
				sf, NULL, NULL, pid, NULL, &error);
		}
	}
	if(error) {
		if(ret)
			ret->push_back(error->message);
		g_error_free (error);
		return;
	}
	vte_terminal_set_scrollback_lines(hr, -1);
}

static pub::tags___ tags_ = {
		{"插入", "i", 1},
		{"文字", "f", 1},
		{"复制", "c", 0},
		{"粘贴", "v", 0},
		{"选择", "s", 0},
		{"工作目录", "d", 0},
		{"pid", "I", 0},
		{"reset", "R", 0},
		{"颜色", "B", 1},
		{"缩放", "S", 1},
		{"命令", "C", 1},
};

bool view___::api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret) {
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y':
		switch(tag[0]) {
		case 'i': {
			if(ins1_) {
				ins1_ = false;
				pub::ext_->wait__("0.1s");
			}
			const std::string& data = p[1];
			//if(!ins_init__(data.c_str()))
				ins__(data);
			break; }
		case 'f': {
			const std::string& data = p[1];
			vte_terminal_feed(hr__(), data.c_str(), data.length());
			break; }
		case 'c':
			if(vte_terminal_get_has_selection(hr__())) {
				vte_terminal_copy_clipboard(hr__());
				ret.push_back("1");
			}
			break;
		case 'v': vte_terminal_paste_clipboard(hr__()); break;
		case 's': {
			GArray *attr = g_array_new(FALSE, FALSE, sizeof(VteCharAttributes));
			gchar *text = vte_terminal_get_text(hr__(), nullptr, nullptr, attr);
			ret.push_back(text);
			g_free (text);
			g_array_free(attr, TRUE);
			break; }
		case 'd': {
			std::string path = "/proc/" + std::to_string(pid_) + "/cwd";
			char buf[512];
			ssize_t n = readlink(path.c_str(), buf, 512);
			if(n > 0) {
				buf[n] = 0;
				ret.push_back(buf);
			}
			break; }
		case 'I':
			ret.push_back(std::to_string(pid_));
			break;
		case 'R':
			vte_terminal_reset(hr__(), true, true);
			break;
		case 'B': {
			int r1, g1, b1, a1, r2, g2, b2, a2;
			float r1f, g1f, b1f, a1f, r2f, g2f, b2f, a2f;
			bool use_f = false;
			const char* s = p[1].c_str();
			GdkRGBA fc, bc;
			if(sscanf(s, "%f,%f,%f,%f:%f,%f,%f,%ff", &r1f, &g1f, &b1f, &a1f, &r2f, &g2f, &b2f, &a2f) == 8) {use_f = true;}
			else if(sscanf(s, "%d,%d,%d,%d:%d,%d,%d,%d", &r1, &g1, &b1, &a1, &r2, &g2, &b2, &a2) == 8 ||
					sscanf(s, "%02x%02x%02x%02x:%02x%02x%02x%02x", &r1, &g1, &b1, &a1, &r2, &g2, &b2, &a2) == 8) {}
			else if(sscanf(s, "%d,%d,%d:%d,%d,%d", &r1, &g1, &b1, &r2, &g2, &b2) == 6 ||
					sscanf(s, "%02x%02x%02x:%02x%02x%02x", &r1, &g1, &b1, &r2, &g2, &b2) == 6)
				a1 = a2 = 255;
			else {
				pub::ext_->buzhichi__(p, SIZE_MAX);
				return true;
			}
			if(!use_f) {
				r1f = r1 / 255.0;
				g1f = g1 / 255.0;
				b1f = b1 / 255.0;
				a1f = a1 / 255.0;
				r2f = r2 / 255.0;
				g2f = g2 / 255.0;
				b2f = b2 / 255.0;
				a2f = a2 / 255.0;
			}
			fc.red = r1f;
			fc.green = g1f;
			fc.blue = b1f;
			fc.alpha = a1f;
			bc.red = r2f;
			bc.green = g2f;
			bc.blue = b2f;
			bc.alpha = a2f;
			vte_terminal_set_color_foreground(hr__(), &fc);
			vte_terminal_set_color_background(hr__(), &bc);
			break; }
		case 'S':
			vte_terminal_set_font_scale(hr__(), std::stod(p[1].c_str()));
			break;
		case 'C':
			cmd__(p, 1, hr__(), &pid_, &ret);
			break;
		}
		return true;
	case '<':
		pub::ext_->buzu__(p, SIZE_MAX);
		return true;
	}
	return pub::view___::api__(shangji, p, p2, ret);
}

void view___::new_open__(const std::vector<std::string>& p) {
	if(p.size() > 0 && !p[0].empty()) {
		cmd__(p, 0, hr__(), &pid_, nullptr);
	}
}

void view___::ins__(const std::string &cmd1) {
	vte_terminal_feed_child(hr__(), cmd1.c_str(), cmd1.length());
}

static gboolean idle1__(gpointer user_data) {
	view___* v = (view___*)user_data;
	v->ins__(v->data_);
#ifdef ver_debug_
	debug_.o__("idle1__", v->data_);
#endif
	return G_SOURCE_REMOVE;
}

bool view___::ins_init__(const char* s) {
	bool ret = false;
	if(!has_init__()) {
		init__();
		ret = true;
	}
	if(!cmd1_) {
		cmd1_ = true;
		const std::string &cmd1 = plugin_->cmd1_;
		if(!cmd1.empty())
			ins__(cmd1);
	}
	if(s) {
		if(ins1_ && init2_by__() == 2) {
			ins1_ = false;
			ret = true;
		}
		if(ret) {
			data_ = s;
			g_idle_add(idle1__, this);
		}
	}
	return ret;
}

static void cb__(VteTerminal* vte, void* data_in) {
	pub::sign___* sign = (pub::sign___*)data_in;
	view___* view = (view___*)sign->data_;
	view->ins_init__(nullptr);
	switch(sign->sig_->flag_) {
	case 't': {
		const char* s = vte_terminal_get_icon_title(vte);
		if(view->title_ != s)
			view->title_ = s;
		else break;
		pub::ext_->jieshi2__(view, sign->sig_->name_, "s", s);
		break; }
	default:
		if(sign->sig_->name_)
			pub::ext_->jieshi2__(view, sign->sig_->name_);
		break;
	}
}
static void cb2__(VteTerminal* vte, int arg1, void* data_in) {
	pub::ext_->jieshi22__(data_in, "s", std::to_string(arg1).c_str());
}

static pub::sigs___ sigs_ = {
		{"contents-changed", G_CALLBACK(cb__), "内容改变", 'c'},
		{"cursor-moved", G_CALLBACK(cb__)},
		{"icon-title-changed"/*"window-title-changed"*/, G_CALLBACK(cb__), "页标题", 't'},
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
