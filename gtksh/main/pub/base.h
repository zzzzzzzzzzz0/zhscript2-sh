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

	void name__(const char *name);
	const char *name__();

	GObject *object__() {return G_OBJECT(hr_);}
	void var__(const char *name, gpointer data);
	gpointer var__(const char *name);
};

} /* namespace pub */

#endif /* PUB_BASE_H_ */
