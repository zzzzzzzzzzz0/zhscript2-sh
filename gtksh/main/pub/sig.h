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
#include <string>

namespace pub {

class sig___;
class sign___ {
public:
	gpointer data_;
	std::string code_;
	sig___* sig_ = nullptr;
	//不另存就出崩溃
	std::string sig_name_;
	void *this_, *this_data_;
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
	void conn__(sig___ *i, gpointer p1, gpointer p2, const char* code);
public:
	sigs___(std::initializer_list<sig___> a) : a_(a) {}
	void conn__(gpointer p1, gpointer p2 = nullptr, const char* code = nullptr);
	bool conn__(const std::string& name, gpointer p1, gpointer p2 = nullptr, const char* code = nullptr);
	bool conn__(char flag, gpointer p1, gpointer p2 = nullptr, const char* code = nullptr);
	void del__(gpointer p1, gpointer p2);
};

} /* namespace pub */

#endif /* PUB_SIG_H_ */
