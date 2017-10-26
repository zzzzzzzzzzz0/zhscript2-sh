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
#include "err.h"
#include "add.h"
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#include <functional>
namespace _p = std::placeholders;

static pub::tags___ tags_ = {
		{"创建", "c", 1},
		{"新开", "n", 1},
		{"屏宽高", "s", 0},
		{"代码", " ", 1},
};

void main___::api__(window___ *window, pub::view___ *view, void* shangji, const std::vector<std::string>& p, std::vector<std::string>& ret) {
	if(view && view->api__(shangji, p, ret))
		return;
	if(window && window->api__(shangji, p, ret))
		return;
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y': {
		switch(tag[0]) {
		case 'c': case 'n': {
			const std::string &name = p[1];
			plugin_item___* pi = plugins_[name];
			if(!pi) {
				err_.o__("无效插件名 ", name);
				return;
			}
			pub::view___* v = pi->p_->new_view__();
			switch(tag[0]) {
			case 'c':
				window_ = new window___(true);
				add___::begin__(v, window_, false);
				mk_suidao__(qu_, window_, v);
				jieshi3__(window_, v, nullptr, nullptr, nullptr, true, p);
				break;
			case 'n': {
				add___::begin__(v, window_);
				jieshi3__((window___*)v->window_, v, nullptr, nullptr, nullptr, true, p);
				break;
			}}
			pub::arg___ noto {"-不激活", -1},
						other {};
			pub::args___ args {&noto, &other};
			if(!args.parse__(p, 1)) {
				err_.o__(p);
				return;
			}
			v->new_open__(other.a_);
			add___::end__(v, noto.a_.size() == 0);
			return; }
		case 's':
			ret.push_back(std::to_string(gdk_screen_width()));
			ret.push_back(std::to_string(gdk_screen_height()));
			return;
		case ' ':
			code_ = p[1];
			return;
		}
		break; }
	case '<':
		err_.buzu__(p);
		return;
	}
	err_.buzhichi__(p);
}

void main___::api__(window___ *window, pub::view___ *view, void* shangji, const std::vector<std::string>& p, void *ret) {
	std::vector<std::string> ret2;
	api__(window, view, shangji, p, ret2);
	bool one = false;
	for(auto i : ret2) {
		l4_.ret_push__(ret, i.c_str(), one);
		if(!one)
			one = true;
	}
}

static void push__(va_list &argv, std::vector<std::string> &p) {
	char* s = va_arg(argv, char*);
	p.push_back(s ? s : "NULL");
}
static void push_end__(int argc, va_list &argv, std::vector<std::string> &p) {
	for (int i = 0; i < argc; ++i)
		push__(argv, p);
	va_end(argv);
}

bool main___::jieshi__(const char* src,const char* src2,void* shangji, bool p_has_src2, const std::vector<std::string>& p, std::vector<std::string> *ret) {
	if(p_has_src2 && p.size() > 0)
		src2 = p[0].c_str();
	size_t from = p_has_src2 ? 1 : 0;
	const char** argv2 = nullptr;
	size_t argc2 = 0;
	if(p.size() > from) {
		argc2 = p.size() - from;
		argv2 = new const char*[argc2];
		for(size_t i = from; i < p.size(); i++)
			argv2[i - from] = p[i].c_str();
	}
	bool ok = l4_.jieshi2__(src ? src : code_.c_str(), false, src2, shangji ? shangji : qu_, argc2, argv2, ret);
	if(argv2)
		delete argv2;
	if(l4_.is_end__())
		window_->destroy__();
	else if(!ok)
		err_.o__(l4_.err__());
	return 	ok;
}
bool main___::jieshi__(const char* src,const char* src2,void* shangji, const char* argc,va_list &argv, std::vector<std::string> *ret) {
	std::vector<std::string> p;
	if(argc) {
		for(int i = 0;; i++) {
			char typ = argc[i];
			if(!typ)
				break;
			switch(typ) {
			case 's':
				push__(argv, p);
				break;
			case 'l': p.push_back(std::to_string(va_arg(argv, long))); break;
			case 'd': p.push_back(std::to_string(va_arg(argv, double))); break;
			case 'p': p.push_back(std::to_string((unsigned long)va_arg(argv, void*))); break;
			default:
				err_.o__("非法格式", argc);
				return false;
			}
		}
		va_end(argv);
	}
	return jieshi__(src, src2, shangji, false, p, ret);
}
bool main___::jieshi__(window___* w, pub::view___ *v, const char* src, const char* src2, void* shangji, const char* argc,va_list &argv) {
	void *qu = nullptr;
	mk_qu__(w, v, shangji, qu);
	bool ok = jieshi__(src, src2, qu ? qu : shangji,argc,argv, nullptr);
	if(qu)
		l4_.delete_qu__(qu);
	return ok;
}
bool main___::jieshi2__(pub::view___ *v, const char* src2, const char* argc,...) {
	va_list argv;
	va_start(argv, argc);
	return jieshi__(nullptr, v, nullptr, src2, nullptr, argc,argv);
}
bool main___::jieshi22__(void* w, const char* src2, const char* argc,...) {
	va_list argv;
	va_start(argv, argc);
	return jieshi__((window___*)w, nullptr, nullptr, src2, nullptr, argc,argv);
}
bool main___::jieshi3__(window___* w, pub::view___ *v, const char* src, const char* src2, void* shangji, bool p_has_src2, const std::vector<std::string>& p, std::vector<std::string> *ret) {
	void *qu = nullptr;
	mk_qu__(w, v, shangji, qu);
	bool ok = jieshi__(src, src2, qu ? qu : shangji, p_has_src2, p, ret);
	if(qu)
		l4_.delete_qu__(qu);
	return ok;
}

bool main___::for_plugin__(const std::string &path) {
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
	return true;
}

static void realpath__(std::string &path) {
	char buf[512] = "";
	readlink(path.c_str(), buf,512);
	if(!buf[0])
		return;
	if(buf[0] == '/')
		path = buf;
	else {
		size_t i = path.rfind('/');
		path = path.substr(0, i + 1) + buf;
	}
	realpath__(path);
}

int main___::main__(int argc, char* argv[]) {
	gtk_init(&argc, &argv);
	/*if(argv[0][0] != '/') {
		std::string s = fs::current_path().string() + "/" + argv[0];
		argv[0] = new char[s.length() + 1];
		s.copy(argv[0], s.length());
	}*/
	{
		std::string line;
		{
			std::string path = argv[0];
			path += ".zs";
			if(exists__(path.c_str()))
				line += "\"" + path + "\"";
			//debug_.o__(line);
		}
		if(!l4_.init__(line.c_str(), argc, argv))
			return -1;
	}
	qu_ = l4_.new_main_qu__();
	mk_suidao2__(qu_);
	mk_suidao__(qu_, nullptr, nullptr);

	pub::ext_ = new pub::ext___();
	pub::ext_->jieshi__ = std::bind(&main___::jieshi3__, this, nullptr, _p::_1, _p::_2, nullptr, _p::_3, _p::_4, _p::_5, _p::_6);
	pub::ext_->jieshi2__ = std::bind(&main___::jieshi2__, this, _p::_1, _p::_2, nullptr);
	pub::ext_->jieshi2s__ = std::bind(&main___::jieshi2__, this, _p::_1, _p::_2, "s", _p::_3);
	pub::ext_->jieshi2ss__ = std::bind(&main___::jieshi2__, this, _p::_1, _p::_2, "ss", _p::_3, _p::_4);
	pub::ext_->jieshi2sss__ = std::bind(&main___::jieshi2__, this, _p::_1, _p::_2, "sss", _p::_3, _p::_4, _p::_5);
	pub::ext_->jieshi3__ = std::bind(&main___::jieshi22__, this, _p::_1, _p::_2, nullptr);
	pub::ext_->err__ = std::bind(&err___::o31__, &err_, _p::_1);
	pub::ext_->buzu__ = std::bind(&err___::buzu__, &err_, _p::_1);
	pub::ext_->buzhichi__ = std::bind(&err___::buzhichi__, &err_, _p::_1);
	pub::ext_->add_begin__ = add___::begin__;
	pub::ext_->add_end__ = add___::end__;
	pub::ext_->close__ = add___::close__;

	{
		std::string path = argv[0];
		realpath__(path);
		if(!for_plugin__(path + "-plugin"))
			return -1;
	}

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
	if(!l4_.is_end__())
		gtk_main();
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

void main___::mk_qu__(window___*& w, pub::view___ *v, void* shangji, void*& qu) {
	if(w || v) {
		qu = l4_.new_qu__(shangji ? shangji : qu_);
		if(!w && v)
			w = (window___ *)v->window_;
		mk_suidao__(qu, w, v);
	}
}

static void suidao__(void *ret, void* shangji,main___* plugin, window___ *w, pub::view___ *v,int argc,...) {
	if(argc <= 0)
		return;
	std::vector<std::string> p;
	va_list argv;
	va_start(argv, argc);
	push_end__(argc, argv, p);
	plugin->api__(w, v, shangji, p, ret);
}

void main___::mk_suidao__(void *qu, window___ *w, pub::view___ *v) {
	l4_.mk_suidao__(qu, "使", (unsigned long)suidao__, false, 3, (unsigned long)this, (unsigned long)w, (unsigned long)v);
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
		std::string wname = p[0], tname;
		{
			size_t i = wname.find("#");
			if(i != std::string::npos) {
				tname = wname.substr(i + 1);
				wname = wname.substr(0, i);
			}
		}
		for(auto i : windows_) {
			const char* name = i->name__();
			if(!name)
				continue;
			if(name == wname) {
				w = i;
				v = add___::get_view__(tname.c_str(), w);
				break;
			}
		}
	}
	p.erase(p.begin());
	plugin->api__(w, v, shangji, p, ret);
}

void main___::mk_suidao2__(void *qu) {
	l4_.mk_suidao__(qu, "直使", (unsigned long)suidao2__, false, 1, (unsigned long)this);
}

static main___ main_;
int main(int argc, char* argv[]) {
	return main_.main__(argc, argv);
}
