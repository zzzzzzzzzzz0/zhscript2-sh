/*
 * view.h
 *
 *  Created on: 2020年07月04日
 *      Author: zzzzzzzzzzz
 */

#ifndef VIEW_H_
#define VIEW_H_

#include "pub/view.h"
#include <webkit2/webkit2.h>

class view___: public pub::view___ {
public:
	view___() : view___(nullptr) {};
	view___(WebKitWebView* wv);
	virtual ~view___();

	WebKitWebView *hr__() {return WEBKIT_WEB_VIEW(hr_);}

	bool api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret);
	void new_open__(const std::vector<std::string>& p);
};

#endif /* VIEW_H_ */
