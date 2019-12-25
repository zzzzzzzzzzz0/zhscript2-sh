/*
 * window.h
 *
 *  Created on: 2017年8月5日
 *      Author: zzzzzzzzzzz
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include "pub/base.h"
#include "pub/data.h"

class window___ : public pub::base___ {
private:
	void *add_ = nullptr;
	GdkCursor *cursor_ = nullptr;
	void stoi__(const std::vector<std::string>& p, int& x, int& y, int* out_x = nullptr, int* out_y = nullptr);
protected:
	bool is_main_;
public:
	int width_ = -1, height_ = -1;
	int x_ = -1, y_ = -1;
	std::string state_;

	window___(bool is_app_paintable = false, bool is_main = false);
	virtual ~window___();

	GtkWindow *hr__() {return GTK_WINDOW(hr_);}
	GdkWindow *hr2__() {return gtk_widget_get_window(hr_);}
	GtkContainer *container__() {return GTK_CONTAINER (hr_);}
	bool is_main__() {return is_main_;}
	void *add__() {return add_;}
	void app_paintable__(GtkWidget *hr);

	bool api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret);

	void destroy__();
};

extern std::vector<window___*> windows_;

#endif /* WINDOW_H_ */
