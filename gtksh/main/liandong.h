/*
 * liandong.h
 *
 *  Created on: 2017年8月10日
 *      Author: zzzzzzzzzzz
 */

#ifndef LIANDONG_H_
#define LIANDONG_H_

#include <string>
#include "window.h"

class liandong___ {
public:
	void add__(window___ *w, const std::string &grpname);
	void del__(window___ *w);
	void window_move__(window___ *w, int x, int y);
	void window_resize__(window___ *w, int w_new, int w_old, int h_new, int h_old);
	void window_state__(window___ *w, unsigned state);
	void window_destroy__(window___ *w);
};

class liandong_pian___ {
public:
	int x_ = 0, y_ = 0;
	bool get_ = false;
	void get__(window___ *w, int x, int y);
};
extern liandong_pian___ liandong_pian_;

#endif /* LIANDONG_H_ */
