/*
 * add.h
 *
 *  Created on: 2017年8月5日
 *      Author: zzzzzzzzzzz
 */

#ifndef ADD_H_
#define ADD_H_

#include "pub/view.h"
#include "pub/addopt.h"
#include "pub/area.h"
#include "pub/plugin.h"
#include <functional>

class add___ {
private:
	GtkWidget *box_ = nullptr, *box1_ = nullptr, *box2_ = nullptr, *box3_ = nullptr, *box4_ = nullptr;
	int i_ = 0;

	void end_1__(pub::view___ * view, pub::add_opt___* opt);
	void pack__(GtkWidget *w, pub::area___ * area, pub::add_opt___* opt);
	static void code__(pub::view___ * view, int i, pub::view___ * view2 = nullptr);
	static bool tofrom__(pub::view___ *view, bool b);
public:
	void del__(void* w);
	static bool mk__(const std::vector<std::string>& p, size_t from, std::vector<pub::data___>* p2);
	static void* new_window__(pub::add_opt___* opt, bool is_main = false);

	static bool begin__(pub::view___ * view, void* w, pub::view___ *from_view, pub::add_opt___* opt);
	static void end__(pub::view___ * view, void* w, pub::add_opt___* opt, std::vector<std::string>* p, pub::plugin___ *p2);
	static void code__(pub::view___ * view);

	static pub::view___ * get_view__(const char *name, void* w);
	static void close__(pub::view___ *);
	static pub::view___* activa__(const std::string &name, bool to, bool to2, GtkNotebook **nb2 = nullptr, int* i2 = nullptr);
	static void curr__(GtkNotebook *nb2, int i2);
	static void for_view__(void* w, std::function<bool(pub::view___*)> fn);

	static bool api__(pub::view___ * view, void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret);
};

#endif /* ADD_H_ */
