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

static std::string true_ = "true", false_ = "false";

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
	const char*ret;
	{
		WebKitWebPage *wp = reinterpret_cast<WebKitWebPage*>(JSObjectGetPrivate(js_function));
		if(!wp)
			return JSValueMakeNull (js_context);
		//WebKitDOMDocument* doc = webkit_web_page_get_dom_document (wp);
		char** argv = new char*[argument_count + 1];
		JSStringRef* jsr = new JSStringRef[argument_count];
		for(size_t i = 0; i < argument_count; i++) {
			jsr[i] = JSValueToStringCopy(js_context, js_arguments[i], js_exception);
			size_t jsSize = JSStringGetMaximumUTF8CStringSize(jsr[i]);
			argv[i] = new char[jsSize];
			JSStringGetUTF8CString(jsr[i], argv[i], jsSize);
		}
		if(!argv[0][0]) {
			ret = NULL;
			for(size_t i = 1; i < argument_count; i++)
				g_message("%s", argv[i]);
		} else {
			//ret=call4__(argv[0],NULL,argument_count,(const char**)argv,1);
			ret = "啊";
		}
		for(size_t i = 0; i < argument_count; i++) {
			delete argv[i];
			JSStringRelease(jsr[i]);
		}
		delete jsr;
		delete argv;
	}

	if(!ret)
		return JSValueMakeNull (js_context);
	JSValueRef ret2;
	if(true_ == ret || false_ == ret)
		ret2 = JSValueMakeBoolean(js_context, true_ == ret);
	else {
		JSStringRef ret1 = JSStringCreateWithUTF8CString(ret);
		ret2 = JSValueMakeString(js_context, ret1);
		JSStringRelease (ret1);
	}
	return ret2;
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
	/*const gchar *uri = webkit_uri_request_get_uri(request);
	g_message("%s", uri);*/
	//return true;
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

extern "C" G_MODULE_EXPORT void webkit_web_extension_initialize(WebKitWebExtension *extension) {
	sigs_.conn__(webkit_script_world_get_default());
	sigs2_.conn__(extension);
}
