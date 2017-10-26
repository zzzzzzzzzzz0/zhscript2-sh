/*
 * window.h
 *
 *  Created on: 2017年8月5日
 *      Author: zzzzzzzzzzz
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <gtk/gtk.h>
#include <vector>
#include <string>

class window___ {
private:
	void *add_ = nullptr;
protected:
	GtkWindow *hr_ = nullptr;
	bool is_main_;
public:
	int width_ = -1, height_ = -1;

	window___(bool is_main = false);
	virtual ~window___();

	GtkWindow *hr__() {return hr_;}
	GtkWidget *widget__() {return GTK_WIDGET(hr_);}
	GtkContainer *container__() {return GTK_CONTAINER (hr_);}
	bool is_main__() {return is_main_;}
	const char *name__() {return gtk_widget_get_name(widget__());}
	void *add__() {return add_;}

	bool api__(void* shangji, const std::vector<std::string>& p, std::vector<std::string>& ret);

	void destroy__();
};

extern std::vector<window___*> windows_;

#endif /* WINDOW_H_ */
