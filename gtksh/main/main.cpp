/*
 * main.cpp
 *
 *  Created on: 2017年8月4日
 *      Author: zzzzzzzzzzz
 */

#include "main.h"
#include "pub/sig.h"
#include "pub/tag.h"
#include "pub/arg.h"
#include "pub/ext.h"
#include "pub/util.h"
#include "err.h"
#include "err2.h"
#include "add.h"
#include "area.h"
#include "util.h"
#include <cstdarg>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#include <functional>
namespace _p = std::placeholders;
#include <sys/time.h>

static void not_block__() {
	while (gtk_events_pending ())
	  gtk_main_iteration ();
}
static long ms__(struct timeval tv) {
	return tv.tv_sec*1000 + tv.tv_usec/1000;
}
bool wait__(const char* s) {
	struct timeval start, end;
	gettimeofday( &start, NULL );
	time_t len;
	char c;
	float f;
	switch(sscanf(s, "%f%c", &f, &c)) {
	case 2:
		switch(c) {
		case 'd':
			f *= 24;
		case 'h':
			f *= 60;
		case 'm':
			f *= 60;
		case 's':
			break;
		default:
			return false;
		}
	case 1:
		len = f * 1000;
		break;
	default:
		return false;
	}
	do {
		not_block__();
		gettimeofday( &end, NULL );
	} while(ms__(end) - ms__(start) < len);
	return true;
}

static void push__(pub::view___ * view, const char* fmt, std::vector<std::string>& p) {
	window___* window = (window___*)view->window_;
	for(int i = 0;; i++) {
		char c = fmt[i];
		if(!c)
			break;
		switch(c) {
		case '#': {
			std::string s = window->name__();
			s += "#";
			s += view->name__();
			p.push_back(s);
			break; }
		case 'n':
			p.push_back(view->name__());
			break;
		case 'w':
			p.push_back(window->name__());
			break;
		case 'o': p.push_back(std::to_string(view->only_)); break;
		case 'i': p.push_back(std::to_string(view->id_)); break;
		case 'f': p.push_back(std::to_string(view->from_)); break;
		case 't': {
			pub::add_opt___* opt2 = &((area___ *)view->area_)->opt_;
			std::string typ;
			switch(opt2->typ_) {
			case 'n':
				typ += "标签页";
				break;
			}
			p.push_back(typ);
			break; }
		case 'a': {
			std::string s;
			s += ((area___ *)view->area_)->opt_.pos_;
			p.push_back(s);
			break; }
		case 'p': {
			pub::plugin___* pi = (pub::plugin___*)view->var__("插件");
			p.push_back(pi->name_);
			break; }
		}
	}
}

extern int add_id_i_;

static pub::tags___ tags_ = {
		{"创建", "c", 0},
		{"新开", "n", 1},
		{"屏宽高", "s", 0},
		{"不堵塞", "b", 0},
		{"等待", "B", 1},
		{"始id", "i", 1},
		{"代码", " ", 1},
		{"错代码", "E", 1},
}, tags_page_ = {
		{"格", "F", 1},
		{"字体", "f", 1},
		{"改id", "i", 1},
};

void main___::api__(window___ *window, pub::view___ *view, void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret) {
	if(view) {
		std::string tag;
		switch(tags_page_.get__(p, tag)) {
		case 'y': {
			switch(tag[0]) {
			case 'F':
				push__(view, p[1].c_str(), ret);
				break;
			case 'f': {
				PangoFontDescription *font_desc = pango_font_description_from_string (p[1].c_str());
				gtk_widget_modify_font (view->widget__(), font_desc);
				pango_font_description_free (font_desc);
				break; }
			case 'i':
				view->id_ = pub::stoul__(p[1]);
				break;
			}
			return; }
		case '<':
			err_.buzu__(p, SIZE_MAX);
			return;
		}
		if(view->api__(shangji, p, p2, ret))
			return;
		if(add___::api__(view, shangji, p, p2, ret))
			return;
	}
	if(window) {
		if(window->api__(shangji, p, p2, ret))
			return;
	}
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y': {
		switch(tag[0]) {
		case 's':
			ret.push_back(std::to_string(gdk_screen_width()));
			ret.push_back(std::to_string(gdk_screen_height()));
			return;
		case 'c': case 'n': {
			pub::add_opt___ opt;
			std::vector<std::string> p3;
			if(!area___::mk__(p, 0, &opt, &p3)) {
				err_.o__(p);
				return;
			}
			plugin_item___* pi = nullptr;
			if(p3.size() > 1) {
				const std::string &name = p3[1];
				if(plugins_.find(name) == plugins_.end()) {
					err_.o__("无效插件名 ", name);
					return;
				}
				pi = plugins_[name];
			}
			std::vector<std::string> p32;
			if(p3.size() > 2)
				p32.insert(p32.end(), p3.begin() + 2, p3.end());
			window___* w;
			pub::view___* v;
			switch(tag[0]) {
			case 'n': {
				w = window ? window : window_;
				std::string name;
				if(!opt.window_name_.empty())
					name += opt.window_name_;
				if(!opt.name_.empty()) {
					if(name.empty())
						name += w->name__();
					name += "#" + opt.name_;
				}
				if(!name.empty()) {
					v = add___::activa__(name);
					if(v) {
						if(!opt.only_switch_) {
							if(opt.use_open_)
								v->new_open__(p32);
							add___::end_3__(v, &p32, true);
						}
						return;
					}
				}
				break; }
			}
			v = opt.first_no_ || !pi ? nullptr : pi->p_->new_view__();
			switch(tag[0]) {
			case 'c':
				window_ = new window___(opt.is_app_paintable_, true);
				w = window_;
				if(!add___::begin__(v, window_, nullptr, &opt)) {
					delete window_;
					return;
				}
				if(v)
					mk_suidao__(qu_, window_, v, p2);
				break;
			case 'n':
				if(!add___::begin__(v, w, view, &opt))
					return;
				break;
			}
			if(v) {
				if(opt.use_open_)
					v->new_open__(p32);
				jieshi_b__(nullptr, v, p3, opt);
				add___::end__(v, nullptr, &opt, &p32, pi->p_);
			} else {
				jieshi_b__(w, nullptr, p3, opt);
				add___::end__(nullptr, w, nullptr, nullptr, nullptr);
			}
			return; }
		case 'b':
			not_block__();
			return;
		case 'B':
			if(!wait__(p[1].c_str()))
				err_.buzhichi__(p, SIZE_MAX);
			return;
		case 'i':
			add_id_i_ = pub::stoul__(p[1]);
			return;
		case ' ':
			code_ = p[1];
			return;
		case 'E':
			err_.code_ = p[1];
			return;
		}
		break; }
	case '<':
		err_.buzu__(p, SIZE_MAX);
		return;
	}
	err_.buzhichi__(p, SIZE_MAX);
}

void main___::jieshi_b__(void* w, pub::view___ *v, std::vector<std::string>& p3, pub::add_opt___& opt) {
	std::vector<pub::data___> p22 {{"o", &opt}};
	jieshi3__(w, v, nullptr, nullptr, nullptr, true, &p3, &p22);
}

void main___::api__(window___ *window, pub::view___ *view, void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, void *ret) {
	std::vector<std::string> ret2;
	{
		bool next = true;
		for(auto i : plugins_) {
			plugin_item___* pi = i.second;
			if(pi->p_->api__(shangji, p, p2, ret2)) {
				next = false;
				break;
			}
		}
		if(next)
			api__(window, view, shangji, p, p2, ret2);
	}
	bool one = false;
	for(auto i : ret2) {
		l4_.ret_push__(ret, i.c_str(), one);
		if(!one)
			one = true;
	}
}

bool main___::jieshi__(const char* src,const char* src2,void* shangji, bool p_has_src2, std::vector<std::string>* p, std::vector<std::string> *ret) {
	if(p_has_src2 && p && p->size() > 0)
		src2 = (*p)[0].c_str();
	size_t from = p_has_src2 ? 1 : 0;
	const char** argv2 = nullptr;
	size_t argc2 = 0;
	if(p && p->size() > from) {
		argc2 = p->size() - from;
		argv2 = new const char*[argc2];
		for(size_t i = from; i < p->size(); i++)
			argv2[i - from] = (*p)[i].c_str();
	}
	bool ok = l4_.jieshi2__(src ? src : code_.c_str(), false, src2, shangji ? shangji : qu_, argc2, argv2, ret);
	if(argv2)
		delete argv2;
	if(!ok) {
		err_.o__(l4_.err__());
		//不应该gtk_main_quit？
	}
	return ok;
}
bool main___::jieshi3__(void* w, pub::view___ *v, const char* src, const char* src2, void* shangji, bool p_has_src2, std::vector<std::string>* p, std::vector<pub::data___>* p2, std::vector<std::string> *ret) {
	void *qu = nullptr;
	{
		window___* w2 = (window___*)w;
		mk_qu__(w2, v, p2, shangji, qu);
	}
	bool ok = jieshi__(src, src2, qu ? qu : shangji, p_has_src2, p, ret);
	if(qu)
		l4_.delete_qu__(qu);
	if(!ok)
		l4_.err_clear__();
	return ok;
}

bool main___::for_plugin__(const std::string &path) {
	try {
		for(auto& p: fs::directory_iterator(path)) {
			if(fs::is_directory(p.status())) {
				if(!for_plugin__(p.path()))
					return false;
				continue;
			}
			std::string so = p.path();
			plugin_item___* pi = new plugin_item___();
			if(!pi->dl_.load__(so.c_str())) {
				err_.o__(so);
				return false;
			}
			{
				using get_plugin___ = pub::plugin___ *(*)(const std::string &);
				get_plugin___ f = reinterpret_cast<get_plugin___>(pi->dl_.get_func__("plugin__"));
				pi->p_ = f(so);
			}
			size_t i1 = so.rfind('/') + 1;
			size_t i2 = so.find('.', i1);
			std::string name = so.substr(i1, i2 - i1);
			pi->p_->name_ = name;
			{
				using set_ext___ = void(*)(pub::ext___ *, pub::plugin___ *);
				set_ext___ f = reinterpret_cast<set_ext___>(pi->dl_.get_func__("ext__"));
				f(pub::ext_, pi->p_);
			}
			plugins_[name] = pi;
		}
	} catch(...) {}
	return true;
}

static void g_log__(const gchar *log_domain, GLogLevelFlags log_level,const gchar *message,gpointer user_data){
	char c=0;
	switch(log_level){
	case G_LOG_LEVEL_CRITICAL:	c='c';break;
	case G_LOG_LEVEL_WARNING:	c='w';break;
	case G_LOG_LEVEL_DEBUG:		c='d';break;
	case G_LOG_LEVEL_MESSAGE:	c='m';break;
	case G_LOG_LEVEL_INFO:		c='i';break;
	case G_LOG_FLAG_RECURSION:	c='r';break;
	case G_LOG_FLAG_FATAL:		c='f';break;
	case G_LOG_LEVEL_ERROR:		c='e';break;
	case G_LOG_LEVEL_MASK:		c='M';break;
	}
	std::cerr<<"log--"<<(log_domain?log_domain:"")<<"--";
	if(c)
		std::cerr<<c;
	else
		std::cerr<<log_level;
	std::cerr<<"--"<<message<<std::endl;
}
int main___::main__(int argc, char* argv[]) {
	{
		GLogLevelFlags llf=(GLogLevelFlags)(G_LOG_LEVEL_MASK);
		g_log_set_handler (NULL, llf, g_log__, NULL);
		g_log_set_handler ("Gtk", llf, g_log__, NULL);
		g_log_set_handler ("Gdk", llf, g_log__, NULL);
		g_log_set_handler ("GLib", llf, g_log__, NULL);
		g_log_set_handler ("GLib-GObject", llf, g_log__, NULL);
	}
	gtk_init(&argc, &argv);
	std::string path = argv[0];
	if(!l4_.init__("", argc, argv, path))
		return -1;
	qu_ = l4_.new_main_qu__();
	err2_.jieshi__ = std::bind(&main___::jieshi__, this, _p::_1, nullptr, qu_, false, nullptr, nullptr);
	static__();
	mk_suidao__(qu_, nullptr, nullptr, nullptr);

	pub::ext_ = new pub::ext___();
	pub::ext_->jieshi__ = std::bind(&main___::jieshi3__, this, _p::_1, _p::_2, _p::_3, _p::_4, _p::_5, _p::_6, _p::_7, _p::_8, _p::_9);
	pub::ext_->err__ = std::bind(&err___::o31__, &err_, _p::_1);
	pub::ext_->buzu__ = std::bind(&err___::buzu__, &err_, _p::_1, _p::_2);
	pub::ext_->buzhichi__ = std::bind(&err___::buzhichi__, &err_, _p::_1, _p::_2);
	pub::ext_->wufa__ = std::bind(&err___::wufa__, &err_, _p::_1, _p::_2);
	pub::ext_->throw__ = std::bind(&err2___::throw__, &err2_, _p::_1, _p::_2);
	pub::ext_->throw2__ = std::bind(&err2___::throw2__, &err2_, _p::_1, _p::_2);
	pub::ext_->throw_buzu__ = std::bind(&err2___::buzu__, &err2_, _p::_1, _p::_2);
	pub::ext_->throw_buzhichi__ = std::bind(&err2___::buzhichi__, &err2_, _p::_1, _p::_2);
	pub::ext_->throw_wufa__ = std::bind(&err2___::wufa__, &err2_, _p::_1, _p::_2);
	pub::ext_->add_begin__ = add___::begin__;
	pub::ext_->jieshi_b__ = std::bind(&main___::jieshi_b__, this, _p::_1, _p::_2, _p::_3, _p::_4);
	pub::ext_->add_end__ = add___::end__;
	pub::ext_->close__ = add___::close__;
	pub::ext_->view__ = area___::view__;
	pub::ext_->push__ = push__;
	pub::ext_->wait__ = wait__;

	if(!for_plugin__(path + "-plugin"))
		return -1;

	if(!l4_.has_src__()) {
		err_.o__("无源");
		return -1;
	}
	if(!l4_.jieshi__(qu_)) {
		if(l4_.is_end__())
			return l4_.exit_code__();
		err_.o__(l4_.err__());
		return -1;
	}
	if(!l4_.is_end__()) {
		loops_ = true;
		gtk_main();
	}
	return l4_.exit_code__();
}

main___::main___() {
}

main___::~main___() {
	for(auto i : plugins_) {
		plugin_item___* pi = i.second;
		delete pi;
	}
	plugins_.clear();
}

void main___::mk_qu__(window___*& w, pub::view___ *v, std::vector<pub::data___>* p2, void* shangji, void*& qu) {
	if(w || v) {
		qu = l4_.new_qu__(shangji ? shangji : qu_);
		if(!w && v)
			w = (window___ *)v->window_;
		mk_suidao__(qu, w, v, p2);
	}
}

static void push__(va_list &argv, std::vector<std::string> &p) {
	char* s = va_arg(argv, char*);
	p.push_back(s ? s : null_);
}
static void push_end__(int argc, va_list &argv, std::vector<std::string> &p) {
	for (int i = 0; i < argc; ++i)
		push__(argv, p);
	va_end(argv);
}

static void suidao__(void *ret, void* shangji,main___* plugin, window___ *w, pub::view___ *v, std::vector<pub::data___>* p2, int argc,...) {
	if(argc <= 0)
		return;
	std::vector<std::string> p;
	va_list argv;
	va_start(argv, argc);
	push_end__(argc, argv, p);
	for(auto i = p.begin(); i != p.end();) {
		const std::string& s = *i;
		if(i == p.begin() && s[0] == '#') {
			v = nullptr;
			if(w) {
				std::string name = w->name__() + s, tname;
				if(util___::for_name__(name, w, tname))
					v = add___::get_view__(tname.c_str(), w);
			}
			if(!v) {
				err_.wufa__(p, 1);
				return;
			}
			i = p.erase(i);
			continue;
		}
		break;
	}
	plugin->api__(w, v, shangji, p, p2, ret);
}

void main___::mk_suidao__(void *qu, window___ *w, pub::view___ *v, std::vector<pub::data___>* p2) {
	l4_.mk_suidao__(qu, "使", (unsigned long)suidao__, false, 4, (unsigned long)this, (unsigned long)w, (unsigned long)v, (unsigned long)p2);
}

static void suidao2__(void *ret, void* shangji,main___* plugin, int argc,...) {
	if(argc <= 1)
		return;
	window___ *w = nullptr;
	pub::view___ *v = nullptr;
	std::vector<std::string> p;
	va_list argv;
	va_start(argv, argc);
	push_end__(argc, argv, p);
	{
		std::string tname;
		if(util___::for_name__(p[0], w, tname))
			v = add___::get_view__(tname.c_str(), w);
	}
	p.erase(p.begin());
	plugin->api__(w, v, shangji, p, nullptr, ret);
}

static main___ main_;

void l4_on_exit__(const char* name) {
	if(main_.window_)
		main_.window_->destroy__();
	else if(main_.loops_)
		gtk_main_quit();
}

void main___::static__() {
	l4_.on_exit__(l4_on_exit__);
	l4_.mk_suidao__(qu_, "直使", (unsigned long)suidao2__, false, 1, (unsigned long)this);
}

int main(int argc, char* argv[]) {
	return main_.main__(argc, argv);
}
