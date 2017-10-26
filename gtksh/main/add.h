/*
 * add.h
 *
 *  Created on: 2017年8月5日
 *      Author: zzzzzzzzzzz
 */

#ifndef ADD_H_
#define ADD_H_

#include "pub/view.h"

class add___ {
private:
	char typ_, typ2_;
	void *widget_ = nullptr;
	bool has_button_, can_close_;

	int i_ = 0;
	add___(char typ, char typ2) : typ_(typ), typ2_(typ2) {}
public:
	virtual ~add___();
	static add___* mk__(char typ, char typ2, const std::vector<std::string>& p);

	void *widget__() {return widget_;}

	static void begin__(pub::view___ * view, void* w, bool from_view = true);
	static void end__(pub::view___ * view, bool to);

	static pub::view___ * get_view__(const char *name, void* w);
	static void close__(pub::view___ *);
};

#endif /* ADD_H_ */
