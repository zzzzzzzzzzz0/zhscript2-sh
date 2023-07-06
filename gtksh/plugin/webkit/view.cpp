/*
 * view.cpp
 *
 *  Created on: 2017年8月6日
 *      Author: zzzzzzzzzzz
 */

#include "view.h"
#include "pub/sig.h"
#include "pub/tag.h"
#include "pub/ext.h"
#include "pub/area.h"
#include "pub/userdata1.h"
#include "pub/util.h"
#include <JavaScriptCore/JavaScript.h>

#ifdef ver_debug_
#include "pub/debug.h"
pub::debug___ debug_;
#endif

static webkit___ *plugin_ = nullptr;

static void s__(const std::string &s, std::string &s2) {
	s2 += '"';
	for(size_t i = 0; i < s.size(); i++) {
		char c = s[i];
		switch(c) {
		case '"':
			s2 += "\\";
			break;
		case '\n':
			s2 += "\\n";
			continue;
		case '\r':
			s2 += "\\r";
			continue;
		}
		s2 += c;
	}
	s2 += '"';
}

static void add__(JSValueRef& value, JSGlobalContextRef& context, std::vector<std::string>& p) {
	/*if (JSValueIsBoolean (context, value)) {
		p.push_back(JSValueToBoolean(context, value) ? "1" : "");
		return;
	}*/
	if(JSValueIsArray(context, value)) {
		JSObjectRef o = JSValueToObject(context, value, NULL);
		JSPropertyNameArrayRef properties = JSObjectCopyPropertyNames(context, o);
		size_t count =  JSPropertyNameArrayGetCount(properties);
		JSPropertyNameArrayRelease(properties);

		for (size_t i = 0; i < count; i++) {
			JSValueRef propertyValue = JSObjectGetPropertyAtIndex(context, o, i, NULL);
			add__(propertyValue, context, p);
		}
		return;
	}

	JSStringRef js_str_value;
	gchar      *str_value;
	gsize       str_length;

	js_str_value = JSValueToStringCopy (context, value, NULL);
	str_length = JSStringGetMaximumUTF8CStringSize (js_str_value);
	str_value = (gchar *)g_malloc (str_length);
	JSStringGetUTF8CString (js_str_value, str_value, str_length);
	JSStringRelease (js_str_value);
	p.push_back(str_value);
	g_free (str_value);
}

static void finished__(GObject *object, GAsyncResult *result, gpointer user_data) {
	WebKitJavascriptResult *js_result;
	GError                 *error = NULL;
	pub::user_data1___* data = (pub::user_data1___*)user_data;

	js_result = webkit_web_view_run_javascript_finish (WEBKIT_WEB_VIEW (object), result, &error);
	if (!js_result) {
		pub::ext_->err__(error->message);
		g_error_free (error);
	} else {
		JSGlobalContextRef context = webkit_javascript_result_get_global_context (js_result);
		JSValueRef value = webkit_javascript_result_get_value (js_result);
		std::vector<std::string> p;
		add__(value, context, p);
		data->jieshi__(&p);
		webkit_javascript_result_unref (js_result);
	}
	delete data;
}

static void run_js__(WebKitWebView *wv, const char* s, pub::user_data1___* ud) {
	if(ud)
		webkit_web_view_run_javascript (wv, s, NULL, finished__, ud);
	else
		webkit_web_view_run_javascript (wv, s, NULL, nullptr, NULL);
}

static void cb_resource_load_started__(WebKitWebView *web_view, WebKitWebResource *resource, WebKitURIRequest *request, gpointer user_data) {
	pub::ext_->jieshi22__(user_data, "s", webkit_uri_request_get_uri(request));
}

static void cb_mouse_target_changed__(WebKitWebView *webView, WebKitHitTestResult *hitTestResult, guint mouseModifiers, gpointer user_data) {
	if (webkit_hit_test_result_context_is_link(hitTestResult)) {
		pub::ext_->jieshi22__(user_data, "ssss", "链接",
				webkit_hit_test_result_get_link_uri(hitTestResult),
				webkit_hit_test_result_get_link_label(hitTestResult),
				webkit_hit_test_result_get_link_title(hitTestResult));
	}
	if (webkit_hit_test_result_context_is_image(hitTestResult)) {
		pub::ext_->jieshi22__(user_data, "ss", "图片", webkit_hit_test_result_get_image_uri (hitTestResult));
	}
	if (webkit_hit_test_result_context_is_media(hitTestResult)) {
		pub::ext_->jieshi22__(user_data, "ss", "媒体", webkit_hit_test_result_get_media_uri (hitTestResult));
	}
}

static pub::sigs___ sigs2_ = {
		{"resource-load-started", G_CALLBACK(cb_resource_load_started__), "请求"},
		{"mouse-target-changed", G_CALLBACK(cb_mouse_target_changed__), "目标"},
};

static pub::tags___ tags_ = {
		{"插脚", "j", 1},
		{"辑令", "e", 1},
		{"页标题", "t", 0},
		{"刷新", "r", 0},
		{"后退", "<", 0},
		{"前进", ">", 0},
		{"网址", "u", 0},
		{"访问", "l", 1},
		{"文本", "lt", 1},
		{"内容", " ", 1},
		{"搜", "s", 1},
		{"缺省字体", "F", 1},
		{"背景色", "B", 1},
		{"禁js", "J", 0},
		{"ua", "@", 0},
		{"缓存", "C", 0},
		{"配置", "S", 0},
		{"侦听", "z", 0},
};

bool view___::api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret) {
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y':
		switch(tag[0]) {
		case 'j':
			run_js__(hr__(), p[1].c_str(), p.size() > 2 ? new pub::user_data1___ {p[2], shangji, this} : nullptr);
			break;
		case 'e': {
			//const char* cmd = WEBKIT_EDITING_COMMAND_COPY;
			const char* cmd = p[1].c_str();
			if(p.size() > 2)
				webkit_web_view_execute_editing_command_with_argument(hr__(), cmd, p[2].c_str());
			else
				webkit_web_view_execute_editing_command(hr__(), cmd);
			break; }
		case 't': {
			const gchar *s = webkit_web_view_get_title (hr__());
			if(s)
				ret.push_back(s);
			break; }
		case 'r':
#ifdef ver_u1704_
			if(code__())
				break;
#endif
			webkit_web_view_reload (hr__());
			break;
		case '<':
			webkit_web_view_go_back (hr__());
			break;
		case '>':
			webkit_web_view_go_forward (hr__());
			break;
		case 'u': {
			const gchar *s = webkit_web_view_get_uri (hr__());
			if(s)
				ret.push_back(s);
			break; }
		case ' ':
			webkit_web_view_load_html(hr__(), p[1].c_str(), p.size() > 2 ? p[2].c_str() : "file:///");
			break;
		case 'l':
			switch(tag[1]) {
			case 't':
				webkit_web_view_load_plain_text(hr__(), p[1].c_str());
				break;
			default:
				load_uri__(p[1]);
				break;
			}
			break;
		case 's': {
			const std::string &s = p[1];
			if(s.empty()) {
			} else {
				WebKitFindOptions fo = WEBKIT_FIND_OPTIONS_CASE_INSENSITIVE;
				for(size_t i = 2; i < p.size(); i++) {
					const std::string s = p[i];
					if(s == "反向") {
						fo = WebKitFindOptions(fo | WEBKIT_FIND_OPTIONS_BACKWARDS);
						continue;
					}
					if(s == "大小写") {
						fo = WebKitFindOptions(fo & ~WEBKIT_FIND_OPTIONS_CASE_INSENSITIVE);
						continue;
					}
					pub::ext_->buzhichi__(p, i);
					return true;
				}
				WebKitFindController *fc = webkit_web_view_get_find_controller(hr__());
				webkit_find_controller_search_finish(fc);
				webkit_find_controller_search (fc, s.c_str(), fo, G_MAXUINT);
				ret.push_back("1");
			}
			break; }
		case 'F':
			webkit_settings_set_default_font_family(set__(), p[1].c_str());
			/*webkit_settings_set_monospace_font_family(set__(), p[1].c_str());
			webkit_settings_set_serif_font_family(set__(), p[1].c_str());
			webkit_settings_set_cursive_font_family(set__(), p[1].c_str());
			webkit_settings_set_fantasy_font_family(set__(), p[1].c_str());
			webkit_settings_set_pictograph_font_family(set__(), p[1].c_str());*/
			break;
		case 'B': {
			GdkRGBA bc;
			unsigned int r, g, b, a;
			if(sscanf(p[1].c_str(), "%02x%02x%02x%02x", &r, &g, &b, &a) == 4) {
				bc.red = r / 255.0;
				bc.green = g / 255.0;
				bc.blue = b / 255.0;
				bc.alpha = a / 255.0;
			} else {
				if(!gdk_rgba_parse (&bc, p[1].c_str())) {
					pub::ext_->buzhichi__(p, 1);
				}
			}
			webkit_web_view_set_background_color(hr__(), &bc);
			break; }
		case 'J':
			webkit_settings_set_enable_javascript (set__(), false);
			break;
		case '@':
			if(p.size() > 1)
				webkit_settings_set_user_agent(set__(), p[1].c_str());
			else
				ret.push_back(webkit_settings_get_user_agent(set__()));
			break;
		case 'C': {
			WebKitWebsiteDataManager *wdm = webkit_web_view_get_website_data_manager(hr__());
			ret.push_back(webkit_website_data_manager_get_disk_cache_directory(wdm));
			break; }
		case 'S': {
			void *wws = webkit_web_view_get_settings(hr__());
			char type = 's';
			for(size_t i = 1; i < p.size();) {
				const std::string& p2 = p[i++];
				if(p2 == "s" || p2 == "b") {
					type = p2[0];
					continue;
				}
				if(i >= p.size()) {
					pub::ext_->buzu__(p, SIZE_MAX);
					return true;
				}
				const std::string& p3 = p[i++];
				switch(type) {
				case 's':
					g_object_set(wws, p2.c_str(), p3.c_str(), NULL);
					break;
				case 'b':
					g_object_set(wws, p2.c_str(), pub::bool__(p3), NULL);
					break;
				}
				return true;
			}
			break; }
		case 'z':
			for(size_t i = 1; i < p.size(); i += 2) {
				const std::string& p1 = p[i];
				size_t i1 = i + 1;
				if(i1 >= p.size()) {
					pub::ext_->buzu__(p, SIZE_MAX);
					return true;
				}
				if(sigs2_.conn__(p1, hr_, this, p[i1].c_str()))
					continue;
				pub::ext_->buzhichi__(p, i);
				return true;
			}
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
	if(p.size() > 0) load_uri__(p[0]);
}
void view___::add_end__(bool is_switch) {
	init__();
#ifdef ver_u1704_
	if(init_p_.size() > 0)
		code__(init_p_[0]);
	else
		code_.clear();
#endif
}
bool view___::is__(const std::string& name1, unsigned long id2) {
	return name1 == plugin_->name_ && id2 == webkit_web_view_get_page_id (hr__());
}

static std::string add_zs_ = "window.z$=function(){" \
	"if(arguments.length==0)return;" \
	"var f=function(i,o){" \
		"var p='';" \
		"if(i>1)p+='、';" \
		"if(Array.isArray(o)){" \
			"for(var i2=0;i2<o.length;i2++)" \
				"p+=f(i2+1,o[i2]);" \
		"}else p+='下原样'+o+'上原样';" \
		"return p;" \
	"};" \
	"var p='';" \
	"for(var i=1;i<arguments.length;i++)" \
		"p+=f(i,arguments[i]);" \
	"return eval(prompt('zhscript:'+arguments[0],p));" \
"};";/**/

#ifdef ver_u1704_
static gboolean idle_code__(gpointer user_data) {
	view___* v = (view___*)user_data;
	std::vector<std::string> ret;
	pub::ext_->jieshi__(nullptr, v, v->code_.c_str(), nullptr, nullptr, false, nullptr, nullptr, &ret);
	//const gchar *content, *base_uri
	webkit_web_view_load_html(v->hr__(),
			("<script>" + add_zs_ + "</script>" +/**/ (ret.size() > 0 ? ret[0] : "")).c_str(),
			ret.size() > 1 ? ret[1].c_str() : "file:///");
	return G_SOURCE_REMOVE;
}
bool view___::code__() {
	if(code_.empty())
		return false;
	g_idle_add(idle_code__, this);
	return true;
}
void view___::code__(const std::string &url) {
	if(code_.empty() && url.find("zhscript:") == 0)
		code_ = url.substr(9);
}
#endif

void view___::load_uri__(const std::string &url) {
#ifdef ver_u1704_
	code__(url);
	if(code__())
		return;
#endif
	webkit_web_view_load_uri(hr__(), url.empty() ? "about:blank" : url.c_str());
}

void view___::focus1__() {
	if(!focus1_) {
		focus1_ = true;
		gtk_widget_grab_focus(hr_);
	}
}

static gboolean cb_close__(WebKitWebView* webView, gpointer user_data) {
	pub::sign___* sign = (pub::sign___*)user_data;
	view___* view = (view___*)sign->data_;
	pub::ext_->jieshi2__(view, sign->sig_->name_);
	pub::ext_->close__(view);
	//delete sign;
	return TRUE;
}

static void cb_load_changed__(WebKitWebView  *web_view, WebKitLoadEvent load_event, gpointer user_data) {
	switch (load_event) {
	case WEBKIT_LOAD_FINISHED:
		((view___*)(((pub::sign___*)user_data)->data_))->focus1__();
	case WEBKIT_LOAD_STARTED:
		run_js__(web_view, add_zs_.c_str(), nullptr);
		break;
	default:
		break;
	}/**/
	const char* s = nullptr;
	switch (load_event) {
	case WEBKIT_LOAD_STARTED:    s = "始"; break;
	case WEBKIT_LOAD_REDIRECTED: s = "重定向"; break;
	case WEBKIT_LOAD_COMMITTED:  s = "确定"; break;
	case WEBKIT_LOAD_FINISHED:   s = "终"; break;
	}
	pub::ext_->jieshi22__(user_data, "s", s);
}

static GtkWidget* cb_create__ (WebKitWebView *web_view, WebKitNavigationAction *navigation_action, gpointer user_data) {
	view___* v = new view___(web_view);
	pub::add_opt___ opt;
	std::vector<std::string> p;
	pub::sign___* sign = (pub::sign___*)user_data;
	pub::sig___* sig = sign->sig_;
	view___* v2 = (view___*)sign->data_;
	pub::add_opt___* opt2 = &((pub::area___*)v2->area_)->opt_;
	opt.copy__(opt2);
	if(opt2->pos_ == 'c' && !opt2->typ_)
		opt.new_window_ = true;
	if(pub::ext_->add_begin__(v, v2->window_, v2, &opt)) {
		WebKitURIRequest *ur = webkit_navigation_action_get_request(navigation_action);
		WebKitNavigationType nt = webkit_navigation_action_get_navigation_type(navigation_action);
		const char* s = nullptr;
		switch(nt) {
		case WEBKIT_NAVIGATION_TYPE_LINK_CLICKED:     s = "链接"; break;
		case WEBKIT_NAVIGATION_TYPE_FORM_SUBMITTED:   s = "提交"; break;
		case WEBKIT_NAVIGATION_TYPE_BACK_FORWARD:     s = "回来"; break;
		case WEBKIT_NAVIGATION_TYPE_RELOAD:           s = "重装载"; break;
		case WEBKIT_NAVIGATION_TYPE_FORM_RESUBMITTED: s = "重提交"; break;
		case WEBKIT_NAVIGATION_TYPE_OTHER:            s = "其他"; break;
		}
		p.push_back(sig->name_);
		p.push_back(plugin_->name_.c_str());
		p.push_back(webkit_uri_request_get_uri (ur));
		p.push_back(s);
		pub::ext_->jieshi_b__(nullptr, v, p, opt);
		p.erase(p.begin(), p.begin() + 2);
		pub::ext_->add_end__(v, nullptr, &opt, &p, plugin_);
	}
	return v->widget__();
}

static gboolean cb_permission_request__(WebKitWebView *web_view, WebKitPermissionRequest *request, gpointer user_data) {
	pub::ext_->jieshi22__(user_data);
	webkit_permission_request_allow (request);
	return TRUE;
}

static gboolean cb_script_dialog__ (WebKitWebView  *web_view, WebKitScriptDialog *dialog, gpointer user_data) {
	pub::sign___* sign = (pub::sign___*)user_data;
	view___* v = (view___*)sign->data_;
	const char* s = webkit_script_dialog_get_message(dialog);
	switch (webkit_script_dialog_get_dialog_type(dialog)) {
	case WEBKIT_SCRIPT_DIALOG_ALERT: {
		std::vector<std::string> p, ret;
		p.push_back("警告");
		p.push_back(s);
		pub::ext_->push__(v, "#", p);
		pub::ext_->jieshi__(nullptr, v, nullptr, sign->sig_->name_, nullptr, false, &p, nullptr, &ret);
		if(ret.size() == 1 && ret[0] == "x")
			return true;
		break; }
	case WEBKIT_SCRIPT_DIALOG_CONFIRM:
		pub::ext_->jieshi2__(v, sign->sig_->name_, "ss", "确认", s);
		break;
	case WEBKIT_SCRIPT_DIALOG_PROMPT: {
		const char* s2 = webkit_script_dialog_prompt_get_default_text(dialog);
		std::string s1 = s;
		const std::string zs = "zhscript:";
		if(s1.find(zs) == 0) {
			s1 = s1.substr(zs.size());
			std::vector<std::string> p, ret;
			pub::ext_->jieshi__(nullptr, v, s2,         nullptr, nullptr, false, &ret, nullptr, &p);
			pub::ext_->jieshi__(nullptr, v, s1.c_str(), nullptr, nullptr, false, &p, nullptr, &ret);
			std::string ret2;
			switch(ret.size()) {
			case 0:
				break;
			case 1:
				if(ret[0] == "true" || ret[0] == "false")
					ret2 = ret[0];
				else
					s__(ret[0], ret2);
				break;
			default:
				ret2 += "[";
				for(auto i : ret) {
					s__(i, ret2);
					ret2 += ",";
				}
				ret2 += "]";
				break;
			}
			webkit_script_dialog_prompt_set_text(dialog, ret2.c_str());
			return true;
		}
		pub::ext_->jieshi2__(v, sign->sig_->name_, "sss", "提问", s, s2);
		break; }
	case WEBKIT_SCRIPT_DIALOG_BEFORE_UNLOAD_CONFIRM:
		break;
	}
	return false;
}

static void cb_title__(WebKitWebView *webView, GParamSpec *pspec, gpointer user_data) {
	pub::ext_->jieshi22__(user_data, "s", webkit_web_view_get_title(webView));
}

#ifdef ver_test_
static GtkActionGroup *gag_ = gtk_action_group_new ("z");
static gboolean
cb_context_menu__ (WebKitWebView       *web_view,
               WebKitContextMenu   *context_menu,
               GdkEvent            *event,
               WebKitHitTestResult *hit_test_result,
               gpointer             user_data) {
	GtkAction* a = gtk_action_group_get_action (gag_, "z");
	WebKitContextMenuItem *item = webkit_context_menu_item_new(a);
	webkit_context_menu_append (context_menu, item);
}
#endif

static pub::sigs___ sigs_ = {
#ifdef ver_test_
		{"context-menu", G_CALLBACK(cb_context_menu__), nullptr},
#endif
		{"notify::title", G_CALLBACK(cb_title__), "页标题"},
		{"load-changed", G_CALLBACK(cb_load_changed__), "装载"},
		{"script-dialog", G_CALLBACK(cb_script_dialog__), "对话框"},
		{"create", G_CALLBACK(cb_create__), "新开"},
		{"permission-request", G_CALLBACK(cb_permission_request__), "权限"},
		{"close", G_CALLBACK(cb_close__), "脚关闭"},
};

view___::view___(WebKitWebView* rv) {
	if(rv)
		hr_ = webkit_web_view_new_with_related_view(rv);
	else
		hr_ = webkit_web_view_new();

	WebKitSettings *wks = set__();
	webkit_settings_set_allow_file_access_from_file_urls(wks, true);
	webkit_settings_set_allow_universal_access_from_file_urls(wks, true);
	webkit_settings_set_enable_developer_extras(wks, true);
	webkit_settings_set_enable_write_console_messages_to_stdout(wks, true);
	webkit_settings_set_enable_webgl(wks, true);

	sigs_.conn__(hr_, this);
}
view___::~view___() {
	sigs_.del__(hr_, this);
	sigs2_.del__(hr_, this);
}

extern "C" void ext__(pub::ext___* ext, pub::plugin___ *plugin) {
	pub::ext_ = ext;
	plugin_ = (webkit___ *)plugin;
}
