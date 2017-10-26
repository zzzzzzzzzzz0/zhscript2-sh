/*
 * view.h
 *
 *  Created on: 2017年8月27日
 *      Author: zzzzzzzzzzz
 */

#ifndef VIEW_H_
#define VIEW_H_

#include "pub/view.h"
#include <gtksourceview/gtksourceview.h>
#include <gtksourceview/gtksourcebuffer.h>

class view___: public pub::view___ {
public:
	view___();
	virtual ~view___();
	GtkSourceView* hr__() {return GTK_SOURCE_VIEW (hr_);}
	GtkTextBuffer* buf2__() {return GTK_TEXT_BUFFER (buf_);}

	bool api__(void* shangji, const std::vector<std::string>& p, std::vector<std::string>& ret);
	void new_open__(const std::vector<std::string>& p);
private:
	GtkSourceBuffer *buf_;
};

#endif /* VIEW_H_ */
