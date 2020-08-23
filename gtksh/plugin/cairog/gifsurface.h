/*
 * gifsurface.h
 *
 *  Created on: 2018年12月8日
 *      Author: zzzzzzzzzzz
 */

#ifndef GIFSURFACE_H_
#define GIFSURFACE_H_

#include <gdk/gdk.h>
#include <string>

class gif_surface___ {
private:
	GdkPixbufAnimation* anim_;
	GdkPixbufAnimationIter *iter_ = nullptr;
	GdkPixbuf *pixbuf_ = nullptr;
	gif_surface___() {}
public:
	gdouble x_, y_;
	GdkWindow *win_ = nullptr;
	bool auto_ = false;
	std::string end_code_, next_code_;

	virtual ~gif_surface___() {}
	static gif_surface___* new__(const char* file);
	GdkPixbuf *pixbuf__() {return pixbuf_;}
	int width__();
	int height__();
	int delay_time__();
	bool next__();
	bool is_end__();
	void redraw__();
};

#endif /* GIFSURFACE_H_ */
