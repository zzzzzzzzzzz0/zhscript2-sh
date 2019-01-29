/*
 * view.h
 *
 *  Created on: 2017年8月27日
 *      Author: zzzzzzzzzzz
 */

#ifndef VIEW_H_
#define VIEW_H_

#include "pub/view.h"
#include <gtksourceview/gtksource.h>

class view___: public pub::view___ {
public:
	view___();
	virtual ~view___();
	GtkWidget *scrolled__() {return sw_;}
	GtkSourceView* hr__() {return GTK_SOURCE_VIEW (hr_);}
	GtkTextView* hr2__() {return GTK_TEXT_VIEW (hr_);}
	GtkTextBuffer* buf2__() {return GTK_TEXT_BUFFER (buf_);}

	bool api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret);
	void new_open__(const std::vector<std::string>& p);
private:
	GtkWidget *sw_;
	GtkSourceBuffer *buf_;
	char* text__(bool is_sel = false);
	void scroll2__(GtkTextIter* ti, bool place = true);
};

#endif /* VIEW_H_ */
