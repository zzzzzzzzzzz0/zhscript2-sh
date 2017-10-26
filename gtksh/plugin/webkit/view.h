/*
 * view.h
 *
 *  Created on: 2017年8月6日
 *      Author: zzzzzzzzzzz
 */

#ifndef VIEW_H_
#define VIEW_H_

#include "pub/view.h"
#include <webkit2/webkit2.h>

class view___: public pub::view___ {
public:
	view___();
	virtual ~view___();

	WebKitWebView *hr__() {return WEBKIT_WEB_VIEW(hr_);}
	WebKitSettings *set__() {return webkit_web_view_get_settings (hr__());}

	bool api__(void* shangji, const std::vector<std::string>& p, std::vector<std::string>& ret);
	void new_open__(const std::vector<std::string>& p);
private:
	void load_uri__(const std::string &url);
};

#endif /* VIEW_H_ */
