/*
 * view.h
 *
 *  Created on: 2020年04月09日
 *      Author: zzzzzzzzzzz
 */

#ifndef VIEW_H_
#define VIEW_H_

#include <libwnck/libwnck.h>
#include <gtk/gtk.h>
#include "pub/view.h"

class view___: public pub::view___ {
public:
	view___();
	virtual ~view___();

	WnckPager *hr__() {return WNCK_PAGER (hr_);}

	bool api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret);
};

#endif /* VIEW_H_ */
