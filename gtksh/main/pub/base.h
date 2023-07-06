/*
 * base.h
 *
 *  Created on: 2017年12月22日
 *      Author: zzzzzzzzzzz
 */

#ifndef PUB_BASE_H_
#define PUB_BASE_H_

#include <string>
#include <map>
#include <vector>
#include <gtk/gtk.h>

namespace pub {

class base___ {
private:
	std::map<std::string, std::string> var_;
	std::string name_;
protected:
	GtkWidget *hr_ = nullptr;
	void var__(const std::vector<std::string>& p, std::vector<std::string>& ret);
public:
	bool only_ = false;
	unsigned long id_ = 0;

	GtkWidget *widget__() {return hr_;}

	void name__(const char *name) {
		//gtk_widget_set_name(widget__(), name);
		name_ = name;
	}
	const char *name__() {
		//return gtk_widget_get_name(widget__());
		return name_.c_str();
	}

	GObject *object__() {return object__(hr_);}
	void var__(const char *name, gpointer data) {var__(hr_, name, data);}
	gpointer var__(const char *name) {return var__(hr_, name);}

	static GObject *object__(GtkWidget *hr) {return G_OBJECT(hr);}
	static void var__(GtkWidget *hr, const char *name, gpointer data) {
		g_object_set_data(object__(hr), name, data);
	}
	static gpointer var__(GtkWidget *hr, const char *name) {
		return g_object_get_data(object__(hr), name);
	}
};

} /* namespace pub */

#endif /* PUB_BASE_H_ */
