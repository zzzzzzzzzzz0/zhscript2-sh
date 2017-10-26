/*
 * sig.h
 *
 *  Created on: 2017年8月5日
 *      Author: zzzzzzzzzzz
 */

#ifndef PUB_SIG_H_
#define PUB_SIG_H_

#include <gtk/gtk.h>
#include <vector>
#include <initializer_list>

namespace pub {

class sig___;
class sign___ {
public:
	gpointer data_;
	sig___* sig_ = nullptr;
};

class sig___ {
public:
	const char* coname_;
	GCallback cb_;
	const char* name_ = nullptr;
	const char flag_ = 0;
	void conn__(gpointer p1, sign___* p2);
	void disconn__(gpointer p1);
//private:
	gulong id_ = 0;
};

class sigs___ {
private:
	std::vector<sig___> a_;
public:
	sigs___(std::initializer_list<sig___> a) : a_(a) {}
	void conn__(gpointer p1, gpointer p2 = nullptr);
	void del__(gpointer p1, gpointer p2);
};

} /* namespace pub */

#endif /* PUB_SIG_H_ */
