/*
 * area.h
 *
 *  Created on: 2017年12月11日
 *      Author: zzzzzzzzzzz
 */

#ifndef AREA_H_
#define AREA_H_

#include "pub/area.h"
#include "window.h"
#include <functional>
#include "pub/view.h"

class area___ : public pub::area___ {
public:
	GtkNotebook *nb__();
	void pack__(GtkWidget *box, char pos, pub::add_opt___* opt, GtkWidget *w);
	static area___ *get__(window___* window, char pos, bool* is_new = nullptr);
	static void for__(window___* window, std::function<bool(area___ *)> fn);
	static bool mk__(const std::vector<std::string>& p, size_t from, pub::add_opt___* opt, std::vector<std::string>* other);
	static void view__(const char *name, window___* window, std::function<void(pub::view___*)> fn,
			std::function<void(pub::view___*, int, GtkNotebook*)> fnn);
	static pub::view___* view__(GtkNotebook *nb, int page_num);
	static pub::view___* view__(void* widget);
};

#endif /* AREA_H_ */
