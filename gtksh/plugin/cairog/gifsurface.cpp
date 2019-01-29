/*
 * gifsurface.cpp
 *
 *  Created on: 2018年12月8日
 *      Author: zzzzzzzzzzz
 */

#include "gifsurface.h"

gif_surface___* gif_surface___::new__(const char* file) {
	gif_surface___* g = nullptr;
	GError *error = NULL;
	GdkPixbufAnimation* a = gdk_pixbuf_animation_new_from_file(file, &error);
	if(a) {
		g = new gif_surface___();
		g->anim_ = a;
		GdkPixbufAnimationIter *i = gdk_pixbuf_animation_get_iter(a, NULL);
		g->iter_ = i;
		if(i) {
			g->pixbuf_ = gdk_pixbuf_animation_iter_get_pixbuf(i);
		}
	}
	if(error) {
		//error->message
		g_error_free (error);
		if(g) {
			delete g;
			g = nullptr;
		}
	}
	return g;
}

int gif_surface___::width__() {
	if(!anim_)
		return 0;
	return gdk_pixbuf_animation_get_width(anim_);
}
int gif_surface___::height__() {
	if(!anim_)
		return 0;
	return gdk_pixbuf_animation_get_height(anim_);
}
int gif_surface___::delay_time__() {
	if(!iter_)
		return -1;
	return gdk_pixbuf_animation_iter_get_delay_time (iter_);
}
bool gif_surface___::next__() {
	if(!iter_)
		return false;
	bool b = gdk_pixbuf_animation_iter_advance(iter_, NULL);
	if(b)
		pixbuf_ = gdk_pixbuf_animation_iter_get_pixbuf(iter_);
	return b;
}
bool gif_surface___::is_end__() {
	if(!iter_)
		return true;
	return gdk_pixbuf_animation_iter_on_currently_loading_frame(iter_);
}

