/*
 * world.cpp
 *
 *  Created on: 2017年6月13日
 *      Author: zzzzzzzzzzz
 */

#include "world.h"
#include "pub/sig.h"
#include <webkit2/webkit-web-extension.h>
#include <JavaScriptCore/JavaScript.h>
#include <string>

#ifdef ver_world_1_
#include "webkit.h"
static webkit___ *plugin_ = nullptr;
#endif
#ifdef ver_world_2_
#include "pub2/l4.h"
static pub2::l4___ l4_;
static std::string allow_url_;
#endif

static std::string true_ = "true", false_ = "false";

static void str2val__(const char* ret, JSContextRef js_context, JSValueRef& ret2) {
	if(true_ == ret || false_ == ret)
		ret2 = JSValueMakeBoolean(js_context, true_ == ret);
	else {
		JSStringRef ret1 = JSStringCreateWithUTF8CString(ret);
		ret2 = JSValueMakeString(js_context, ret1);
		JSStringRelease (ret1);
	}
}

static JSValueRef
zs__                (JSContextRef     js_context,
                     JSObjectRef      js_function,
                     JSObjectRef      js_this,
                     size_t           argument_count,
                     const JSValueRef js_arguments[],
                     JSValueRef*      js_exception)
{
	if(argument_count <= 0)
		return JSValueMakeNull (js_context);
	std::vector<std::string> ret;
	{
		WebKitWebPage *wp = reinterpret_cast<WebKitWebPage*>(JSObjectGetPrivate(js_function));
		if(!wp)
			return JSValueMakeNull (js_context);
		//WebKitDOMDocument* doc = webkit_web_page_get_dom_document (wp);
		std::string code;
		std::vector<std::string> p;
		for(size_t i = 0; i < argument_count; i++) {
			JSStringRef jsr = JSValueToStringCopy(js_context, js_arguments[i], js_exception);
			size_t jsSize = JSStringGetMaximumUTF8CStringSize(jsr);
			char* s = new char[jsSize];
			JSStringGetUTF8CString(jsr, s, jsSize);
			switch(i) {
			case 0:
				code = s;
				break;
			default:
				p.push_back(s);
				break;
			}
			delete s;
			JSStringRelease(jsr);
		}
#ifdef ver_world_1_
		if(!plugin_->zs__(webkit_web_page_get_id (wp), code, p, ret)) {
		}
#endif
#ifdef ver_world_2_
		if(code == ".") {
			if(p.size() > 0) {
				for(;;) {
					if(p[0] == "拦截") {
						if(p.size() > 1)
							allow_url_ = p[1];
						else
							allow_url_.clear();
						break;
					}
					break;
				}
			}
			return JSValueMakeUndefined (js_context);
		}
		if(l4_.jieshi3__(code.c_str(), false, nullptr, nullptr, nullptr, &p, &ret) <= 0)
			return JSValueMakeUndefined (js_context);
#endif
	}

	switch(ret.size()) {
	case 0:
		break;
	case 1: {
		JSValueRef ret2;
		str2val__(ret[0].c_str(), js_context, ret2);
		return ret2; }
	default:
		g_message("array[%lu]", ret.size());
		break;
	}
	return JSValueMakeUndefined (js_context);
}

static void cb_window_object_cleared__(WebKitScriptWorld *world, WebKitWebPage *web_page, WebKitFrame *frame, gpointer user_data) {
	JSGlobalContextRef ctx = webkit_frame_get_javascript_context_for_script_world (frame, world);
	const char* name0 = "Z$";
	JSStringRef name = JSStringCreateWithUTF8CString(name0);

	JSObjectRef func;
	{
		JSClassDefinition cd = kJSClassDefinitionEmpty;
		cd.className = name0;
		cd.callAsFunction = zs__;
		JSClassRef cr = JSClassCreate (&cd);
		func = JSObjectMake (ctx, cr, NULL);
	}

	JSObjectRef o = JSContextGetGlobalObject(ctx);
	JSObjectSetProperty(ctx, o, name, func, kJSPropertyAttributeNone, NULL);
	JSStringRelease(name);
	JSObjectSetPrivate(func, web_page);
}

static pub::sigs___ sigs_ = {
		{"window-object-cleared", G_CALLBACK(cb_window_object_cleared__)},
};

static gboolean cb_send_request__(WebKitWebPage *web_page, WebKitURIRequest *request,
		WebKitURIResponse *redirected_response, gpointer user_data) {
	const char* uri = webkit_uri_request_get_uri(request);
#ifdef ver_world_1_
	if(!plugin_->allow__(uri))
		return true;
#endif
#ifdef ver_world_2_
	{
		std::vector<std::string> p, ret;
		p.push_back(uri);
		l4_.jieshi3__(allow_url_.c_str(), false, nullptr, nullptr, nullptr, &p, &ret);
		for(size_t i = 0; i < ret.size(); i++)
			g_message("%u) %s", i, ret[i].c_str());
		switch(ret.size()) {
		case 0:
			break;
		default:
			if(ret[0] == "x") {
				if(ret.size() > 1) {
					webkit_uri_request_set_uri (request, ret[1].c_str());
					break;
				}
				return true;
			}
			return true;
		}
	}
#endif
	return FALSE;
}

static pub::sigs___ sigs3_ = {
		{"send-request", G_CALLBACK(cb_send_request__)},
};

static void cb_page_created__(WebKitWebExtension *extension, WebKitWebPage *web_page, gpointer user_data) {
	sigs3_.conn__(web_page);
}

static pub::sigs___ sigs2_ = {
		{"page-created", G_CALLBACK(cb_page_created__)},
};

world___::world___() {
}

world___::~world___() {
}

extern "C" G_MODULE_EXPORT void
//webkit_web_extension_initialize(WebKitWebExtension *extension)
webkit_web_extension_initialize_with_user_data (WebKitWebExtension *extension, GVariant *user_data)
{
	sigs_.conn__(webkit_script_world_get_default());
	sigs2_.conn__(extension);
#ifdef ver_world_1_
	plugin_ = (webkit___ *)g_variant_get_uint64 (user_data);
#endif
#ifdef ver_world_2_
	l4_.init__(g_variant_get_string(user_data, nullptr));
#endif
}
