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

static void cmd__(const std::vector<std::string>& p, size_t from, VteTerminal* hr, view___* thiz, std::vector<std::string>* ret) {
	GError *error = NULL;
	char **argv = NULL;
	int argc = 0;
	{
		std::string arg = p[from];
		if(plugin_->arg1_.find(arg) == 0)
			arg = plugin_->arg1_;
		g_shell_parse_argv(arg.c_str(), &argc, &argv, &error);
	}
	bool can = true;
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
			const char *wd = nullptr;
			if(p.size() > i && !p[i].empty()) {
				thiz->wd_ = p[i];
				wd = p[i].c_str();
				if(!pub::ext_->exists_(wd)) {
					can = false;
				}
			}
			if(can)
				vte_terminal_spawn_sync(hr, pf, wd, argv, envv, sf, NULL, NULL, &thiz->pid_, NULL, &error);
		}
		g_strfreev(envv);
	}
	g_strfreev(argv);
	if(error) {
		if(ret)
			ret->push_back(error->message);
		g_error_free (error);
		return;
	}
	if(!can)
		return;
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
		{"刷新", "R0", 0},
		{"机插", "A", 1},
		{"颜色", "B", 0},
		{"缩放", "S", 1},
		{"命令", "C", 1},
		{"行数", "l", 1},
		{"无滚动条", "!s", 0},
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
			if(!ins_idle__(data.c_str()))
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
			if(pid_) {
				std::string path = "/proc/" + std::to_string(pid_) + "/cwd";
				char buf[512];
				ssize_t n = readlink(path.c_str(), buf, 512);
				if(n > 0) {
					buf[n] = 0;
					ret.push_back(buf);
				}
			} else
				ret.push_back(wd_);
			break; }
		case 'I':
			ret.push_back(std::to_string(pid_));
			break;
		case 'R':
			switch(tag[1]) {
			case '0':
				if(!pid_) {
					cmd__(init_p_, 0, hr__(), this, &ret);
				}
				break;
			default:
				vte_terminal_reset(hr__(), true, true);
				col_old_ = row_old_ = 0;
				text_old_.clear();
				break;
			}
			break;
		case 'A':
			autoins_ = p[1];
			break;
		case 'B':
			if(p.size() > 1) {
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
				color_ = s;
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
			} else
				ret.push_back(color_);
			break;
		case 'S':
			vte_terminal_set_font_scale(hr__(), std::stod(p[1].c_str()));
			break;
		case 'C':
			cmd__(p, 1, hr__(), this, &ret);
			break;
		case 'l':
			vte_terminal_set_scrollback_lines(hr__(), std::stoi(p[1].c_str()));
			break;
		case '!':
			scroll_ = false;
			break;
		}
		return true;
	case '<':
		pub::ext_->buzu__(p, SIZE_MAX);
		return true;
	}
	return pub::view___::api__(shangji, p, p2, ret);
}

void view___::new_open__(const std::vector<std::string>& p, bool is_new) {
	if(p.size() > 0 && !p[0].empty()) {
		cmd__(p, 0, hr__(), this, nullptr);
	}
}

void view___::text_old__() {
	glong col, row;
	vte_terminal_get_cursor_position(hr__(), &col, &row);
	gchar *vte_text = vte_terminal_get_text_range(hr__(),
			row_old_,
			col_old_,
			row,
			col,
			NULL,
			NULL,
			NULL);
	text_old_ += vte_text;
	g_free (vte_text);

	bool clear = text_old_.size() > 1024;
	{
		const std::string zs = "#zs#";
		size_t i = text_old_.find(zs);
		if(i != std::string::npos) {
			i += zs.size();
			size_t i2 = text_old_.find("\n", i);
			if(i2 != std::string::npos) {
				std::string s = text_old_.substr(i, i2);
				//printf("%s\n",s.c_str());
				pub::ext_->jieshi__(nullptr, this, s.c_str(), zs.c_str(), nullptr, false, nullptr, nullptr, nullptr);
				clear = true;
			}
		}
	}
	if(!autoins_.empty() && (clear || text_old_.size() > 6)) {
		std::vector<std::string> p;
		p.push_back(text_old_);
		pub::ext_->jieshi__(nullptr, this, autoins_.c_str(), nullptr, nullptr, false, &p, nullptr, nullptr);
		clear = true;
	}

	if(clear) {
		text_old_.clear();
	}
	row_old_ = row;
	col_old_ = col;
}

void view___::ins__(const std::string &cmd1) {
	vte_terminal_feed_child(hr__(), cmd1.c_str(), cmd1.length());
}

static gboolean idle_ins__(gpointer user_data) {
	view___* v = (view___*)user_data;
	v->ins__(v->data_);
#ifdef ver_debug_
	debug_.o__("idle1__", v->data_);
#endif
	return G_SOURCE_REMOVE;
}

bool view___::ins_idle__(const char* s) {
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
			g_idle_add(idle_ins__, this);
		}
	}
	return ret;
}

static gboolean idle_focus__(gpointer user_data) {
	gtk_widget_grab_focus(((view___*)user_data)->widget__());
	return G_SOURCE_REMOVE;
}

void view___::focus1__() {
	if(!focus1_) {
		focus1_ = true;
		g_idle_add(idle_focus__, this);
	}
}

static void cb__(VteTerminal* vte, void* data_in) {
	pub::sign___* sign = (pub::sign___*)data_in;
	view___* view = (view___*)sign->data_;
	pub::sig___* sig = sign->sig_;
	//printf("%s %c\n",sig->name_,sig->flag_);
	if(!view->has_init__()) {
		view->init__();
	}
	view->focus1__();
	switch(sig->flag_) {
	case 't': case 'T': {
		const char* s = vte_terminal_get_icon_title(vte);
		if(!s) {
			s = vte_terminal_get_window_title(vte);
			if(!s)
				break;
		}
		if(view->title_ != s)
			view->title_ = s;
		else break;
		pub::ext_->jieshi2__(view, sig->name_, "s", s);
		break; }
	case 'c':
		view->text_old__();
		view->ins_idle__(nullptr);
		break;
	default:
		if(sig->name_)
			pub::ext_->jieshi2__(view, sig->name_);
		break;
	}
}
static void child_exited__(VteTerminal* vte, int arg1, void* data_in) {
	pub::ext_->jieshi22__(data_in, "iii", arg1, arg1 / 256, arg1 % 256);
}

static pub::sigs___ sigs_ = {
		{"contents-changed", G_CALLBACK(cb__), nullptr, 'c'},
		{"cursor-moved", G_CALLBACK(cb__)},
		{"icon-title-changed", G_CALLBACK(cb__), "页标题", 't'},
		{"window-title-changed", G_CALLBACK(cb__), "页标题", 'T'},
		{"child-exited", G_CALLBACK(child_exited__), "内退"},
};

view___::view___() {
	box_ = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_set_homogeneous(GTK_BOX(box_), FALSE);
	hr_ = vte_terminal_new();
	gtk_box_pack_start(GTK_BOX(box_), hr_, TRUE, TRUE, 0);
	pub::ext_->jieshi2__(this, "始前");
	if(scroll_) {
		GtkWidget *scrollbar = gtk_scrollbar_new(GTK_ORIENTATION_VERTICAL,
				gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(hr__())));
		gtk_box_pack_end(GTK_BOX(box_), scrollbar, FALSE, FALSE, 0);
	}

	sigs_.conn__(hr_, this);
}

view___::~view___() {
	sigs_.del__(hr_, this);
}

extern "C" void ext__(pub::ext___* ext, pub::plugin___ *plugin) {
	pub::ext_ = ext;
	plugin_ = (vte___ *)plugin;
}
