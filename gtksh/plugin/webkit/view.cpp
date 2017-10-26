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
#include <JavaScriptCore/JavaScript.h>
#include "webkit.h"

static webkit___ *plugin_ = nullptr;

class user_data1___ {
public:
	std::string code_;
	void* shangji_;
	view___* view_;
};

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
	user_data1___* data = (user_data1___*)user_data;

	js_result = webkit_web_view_run_javascript_finish (WEBKIT_WEB_VIEW (object), result, &error);
	if (!js_result) {
		pub::ext_->err__(error->message);
		g_error_free (error);
	} else {
		JSGlobalContextRef context = webkit_javascript_result_get_global_context (js_result);
		JSValueRef value = webkit_javascript_result_get_value (js_result);
		std::vector<std::string> p;
		add__(value, context, p);
		pub::ext_->jieshi__(data->view_, data->code_.c_str(), /*data->shangji_*/nullptr, false, p, nullptr);
		webkit_javascript_result_unref (js_result);
	}
	delete data;
}

static void run_js__(WebKitWebView *wv, const char* s, user_data1___* ud) {
	if(ud)
		webkit_web_view_run_javascript (wv, s, NULL, finished__, ud);
	else
		webkit_web_view_run_javascript (wv, s, NULL, nullptr, NULL);
}

static pub::tags___ tags_ = {
		{"插脚", "j", 1},
		{"页标题", "t", 0},
		{"网址", "u", 0},
		{"访问", "l", 1},
		{"文本", "lt", 1},
		{"内容", " ", 1},
		{"禁js", "J", 0},
		{"ua", "@", 1},
};

bool view___::api__(void* shangji, const std::vector<std::string>& p, std::vector<std::string>& ret) {
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y':
		switch(tag[0]) {
		case 'j':
			run_js__(hr__(), p[1].c_str(), p.size() > 2 ? new user_data1___ {p[2], shangji, this} : nullptr);
			break;
		case 't': {
			const gchar *s = webkit_web_view_get_title (hr__());
			if(s)
				ret.push_back(s);
			break; }
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
		case 'J':
			webkit_settings_set_enable_javascript (set__(), false);
			break;
		case '@':
			webkit_settings_set_user_agent(set__(), p[1].c_str());
			break;
		}
		return true;
	case '<':
		pub::ext_->buzu__(p);
		return true;
	}
	return pub::view___::api__(shangji, p, ret);
}

void view___::new_open__(const std::vector<std::string>& p) {
	if(p.size() > 1) {
		const std::string &url = p[1];
		if(!url.empty())
			load_uri__(url);
	}
}

void view___::load_uri__(const std::string &url) {
	webkit_web_view_load_uri(hr__(), url.empty() ? "about:blank" : url.c_str());
}

static gboolean cb_close__(WebKitWebView* webView, gpointer user_data) {
	//g_message("Closing Web View");
	pub::sign___* sign = (pub::sign___*)user_data;
	view___* view = (view___*)sign->data_;
	pub::ext_->jieshi2__(view, sign->sig_->name_);
	pub::ext_->close__(view);
	delete sign;
	return TRUE;
}

static void cb_load_changed__(WebKitWebView  *web_view, WebKitLoadEvent load_event, gpointer user_data) {
	switch (load_event) {
	case WEBKIT_LOAD_STARTED:
	case WEBKIT_LOAD_FINISHED:
		{
			std::string s = "window.z$=function(){" \
					"if(arguments.length==0)return;" \
					"var arg='';" \
					"for(var i=1;i<arguments.length;i++){" \
					"if(i>1)arg+='、';" \
					"arg+='下原样'+arguments[i]+'上原样';" \
					"}" \
					"return eval(prompt('zhscript:'+arguments[0],arg));" \
					"};";
			run_js__(web_view, s.c_str(), nullptr);
		}
		break;
	default:
		break;
	}
	pub::sign___* sign = (pub::sign___*)user_data;
	const char* s = nullptr;
	switch (load_event) {
	case WEBKIT_LOAD_STARTED:    s = "始"; break;
	case WEBKIT_LOAD_REDIRECTED: s = "重定向"; break;
	case WEBKIT_LOAD_COMMITTED:  s = "确定"; break;
	case WEBKIT_LOAD_FINISHED:   s = "终"; break;
	}
	pub::ext_->jieshi2s__((view___*)sign->data_, sign->sig_->name_, s);
}

static void cb_resource_load_started__(WebKitWebView *web_view, WebKitWebResource *resource, WebKitURIRequest *request, gpointer user_data) {
	const gchar* uri = webkit_uri_request_get_uri(request);
	//g_message("%s", uri);
	pub::sign___* sign = (pub::sign___*)user_data;
	std::string uri2 = uri;
	if(uri2.find("zhscript:") == 0) {
		webkit_uri_request_set_uri (request, "about:blank");
	}
	pub::ext_->jieshi2s__((view___*)sign->data_, sign->sig_->name_, uri);
}

static GtkWidget* cb_create__ (WebKitWebView *web_view, WebKitNavigationAction *navigation_action, gpointer user_data) {
	pub::sign___* sign = (pub::sign___*)user_data;
	pub::sig___* sig = sign->sig_;
	view___* v = new view___();
	pub::ext_->add_begin__(v, ((view___*)sign->data_)->window_, true);
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
	pub::ext_->jieshi2sss__(v, sig->name_, plugin_->name_.c_str(), webkit_uri_request_get_uri (ur), s);
	pub::ext_->add_end__(v, true);
	return v->widget__();
}

static gboolean cb_permission_request__(WebKitWebView *web_view, WebKitPermissionRequest *request, gpointer user_data) {
	pub::sign___* sign = (pub::sign___*)user_data;
	pub::ext_->jieshi2__((view___*)sign->data_, sign->sig_->name_);
	webkit_permission_request_allow (request);
	return TRUE;
}

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

static gboolean cb_script_dialog__ (WebKitWebView  *web_view, WebKitScriptDialog *dialog, gpointer user_data) {
	pub::sign___* sign = (pub::sign___*)user_data;
	view___* v = (view___*)sign->data_;
	const char* s = webkit_script_dialog_get_message(dialog);
	switch (webkit_script_dialog_get_dialog_type(dialog)) {
	case WEBKIT_SCRIPT_DIALOG_ALERT:
		pub::ext_->jieshi2ss__(v, sign->sig_->name_, "警告", s);
		break;
	case WEBKIT_SCRIPT_DIALOG_CONFIRM:
		pub::ext_->jieshi2ss__(v, sign->sig_->name_, "确认", s);
		break;
	case WEBKIT_SCRIPT_DIALOG_PROMPT: {
		const char* s2 = webkit_script_dialog_prompt_get_default_text(dialog);
		std::string s1 = s;
		const std::string zs = "zhscript:";
		if(s1.find(zs) == 0) {
			s1 = s1.substr(zs.size());
			std::vector<std::string> p, ret;
			pub::ext_->jieshi__(v, s2,         nullptr, false, ret, &p);
			pub::ext_->jieshi__(v, s1.c_str(), nullptr, false, p, &ret);
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
		} else
			pub::ext_->jieshi2sss__(v, sign->sig_->name_, "提问", s, s2);
		break; }
	case WEBKIT_SCRIPT_DIALOG_BEFORE_UNLOAD_CONFIRM:
		break;
	}
	return false;
}

static pub::sigs___ sigs_ = {
		{"resource-load-started", G_CALLBACK(cb_resource_load_started__), "请求"},
		{"load-changed", G_CALLBACK(cb_load_changed__), "装载"},
		{"script-dialog", G_CALLBACK(cb_script_dialog__), "对话框"},
		{"create", G_CALLBACK(cb_create__), "新开"},
		{"permission-request", G_CALLBACK(cb_permission_request__), "权限请求"},
		{"close", G_CALLBACK(cb_close__), "脚关闭"},
};

view___::view___() {
	//WebKitWebContext *wkwc = webkit_web_context_get_default();
	hr_ = webkit_web_view_new();

	WebKitSettings *wks = set__();
	webkit_settings_set_allow_file_access_from_file_urls(wks, true);
	webkit_settings_set_allow_universal_access_from_file_urls(wks, true);
	webkit_settings_set_enable_developer_extras(wks, true);
	webkit_settings_set_enable_write_console_messages_to_stdout(wks, true);

	sigs_.conn__(hr_, this);
}
view___::~view___() {
	sigs_.del__(hr_, this);
}

extern "C" void ext__(pub::ext___* ext, pub::plugin___ *plugin) {
	pub::ext_ = ext;
	plugin_ = (webkit___ *)plugin;
}
