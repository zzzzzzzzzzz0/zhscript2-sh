/*
 * webkit.cpp
 *
 *  Created on: 2017年8月4日
 *      Author: zzzzzzzzzzz
 */

#include "webkit.h"
#include "view.h"
#include "pub/ext.h"
#include "pub/tag.h"

static pub::tags___ tags_ = {
		{"cookie", "c", 1},
		{"代理", "#", 1},
};

bool webkit___::api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret) {
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y':
		switch(tag[0]) {
		case 'c': {
			WebKitWebContext* c;
			/*WebKitWebsiteDataManager* wdm = webkit_website_data_manager_new("base-cache-directory", p[2].c_str(), NULL);
			c = webkit_web_context_new_with_website_data_manager(wdm);
			g_object_unref(wdm);*/
			c = webkit_web_context_get_default();
			WebKitCookieManager* cm = webkit_web_context_get_cookie_manager(c);
			const std::string& file = p[1];
			std::string txt = ".txt";
			size_t i = file.rfind(txt), i2 = file.length() > txt.length() ? file.length() - txt.length() : 0;
			webkit_cookie_manager_set_persistent_storage(cm, file.c_str(), i == i2 ?
					WEBKIT_COOKIE_PERSISTENT_STORAGE_TEXT :
					WEBKIT_COOKIE_PERSISTENT_STORAGE_SQLITE);
			WebKitCookieAcceptPolicy cap = WEBKIT_COOKIE_POLICY_ACCEPT_ALWAYS;
			webkit_cookie_manager_set_accept_policy(cm, cap);
			break; }
		case '#': {
			WebKitNetworkProxySettings* s = webkit_network_proxy_settings_new(p[1].c_str(), nullptr);
			webkit_web_context_set_network_proxy_settings(webkit_web_context_get_default(), WEBKIT_NETWORK_PROXY_MODE_CUSTOM, s);
			webkit_network_proxy_settings_free(s);
			break; }
		}
		return true;
	case '<':
		pub::ext_->buzu__(p, SIZE_MAX);
		return true;
	}
	return pub::plugin___::api__(shangji, p, p2, ret);
}

pub::view___* webkit___::new_view__() {
	return new view___();
}

#ifndef ver_u1704_
static void cb_uri_scheme_request__ (WebKitURISchemeRequest *request, gpointer user_data) {
	std::vector<std::string> ret;
	{
		gchar *code = g_uri_unescape_string(webkit_uri_scheme_request_get_path (request), NULL);
		pub::ext_->jieshi__(nullptr, pub::ext_->view__(webkit_uri_scheme_request_get_web_view(request)),
				code, nullptr, nullptr, false, nullptr, nullptr, &ret);
		switch(ret.size()) {
		case 1: case 2:
			g_free(code);
			break;
		default: {
			GError *error = g_error_new (0, 0, "%s", code);
			g_free(code);
			webkit_uri_scheme_request_finish_error (request, error);
			g_error_free (error);
			return; }
		}
	}
	GInputStream *stream;
	if(ret.size() > 1 && ret[1].empty()) {
		GFile *file = g_file_new_for_path(ret[0].c_str());
		//GFileInputStream *
		stream = (GInputStream *)g_file_read(file, NULL, NULL);
		webkit_uri_scheme_request_finish(request, stream, -1, NULL);
		g_object_unref(file);
	} else {
		const std::string &contents = ret[0];
		gsize stream_length = contents.length();
		stream = g_memory_input_stream_new_from_data (contents.c_str(), stream_length, nullptr);
		webkit_uri_scheme_request_finish (request, stream, stream_length,
				ret.size() > 1 ? ret[1].c_str() : "text/html");
	}
	g_object_unref (stream);
}
#endif

webkit___::webkit___() {
#ifndef ver_u1704_
	WebKitWebContext *wkwc = webkit_web_context_get_default();
	webkit_web_context_register_uri_scheme(wkwc, "zhscript", cb_uri_scheme_request__, NULL, NULL);

	WebKitSecurityManager *wksm = webkit_web_context_get_security_manager(wkwc);
	webkit_security_manager_register_uri_scheme_as_local(wksm, "zhscript");
	/*webkit_security_manager_register_uri_scheme_as_secure(wksm, "zhscript");
	webkit_security_manager_register_uri_scheme_as_cors_enabled(wksm, "zhscript");*/
#endif
}

static webkit___ plugin_;
extern "C" void *plugin__(const std::string &path) {
	std::string dir = path.substr(0, path.rfind('/'));
	//g_message("%s", dir.c_str());
	webkit_web_context_set_web_extensions_directory(webkit_web_context_get_default(), dir.c_str());
	return &plugin_;
}
