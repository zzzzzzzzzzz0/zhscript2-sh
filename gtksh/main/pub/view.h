/*
 * view.h
 *
 *  Created on: 2017年8月5日
 *      Author: zzzzzzzzzzz
 */

#ifndef PUB_VIEW_H_
#define PUB_VIEW_H_

#include <gtk/gtk.h>
#include <string>
#include <vector>

namespace pub {

class view___ {
protected:
	GtkWidget *hr_ = nullptr;
public:
	void* window_ = nullptr;

	view___() {}
	virtual ~view___() {}

	GtkWidget *widget__() {return hr_;}
	GObject *object__() {return G_OBJECT(hr_);}
	virtual GtkWidget *scrolled__() {return hr_;}
	const char *name__() {return gtk_widget_get_name(widget__());}
	void var__(const char *name, gpointer data);
	gpointer var__(const char *name);

	virtual bool api__(void* shangji, const std::vector<std::string>& p, std::vector<std::string>& ret);
	virtual void new_open__(const std::vector<std::string>& p) {}
};

} /* namespace pub */

#endif /* PUB_VIEW_H_ */
