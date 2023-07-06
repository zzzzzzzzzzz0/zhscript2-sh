/*
 * view.h
 *
 *  Created on: 2017年09月12日
 *      Author: zzzzzzzzzzz
 */

#ifndef VIEW_H_
#define VIEW_H_

#include "pub/view.h"
#include <vte/vte.h>

class view___: public pub::view___ {
private:
	GtkWidget *box_;

	bool cmd1_ = false, ins1_ = true, scroll_ = true;
	std::string color_, autoins_;

	glong col_old_ = 0, row_old_ = 0;
	std::string text_old_;

	bool focus1_ = false;
public:
	GPid pid_ = 0;
	std::string wd_, title_, data_;

	view___();
	virtual ~view___();

	GtkWidget *scrolled__() {return box_;}
	VteTerminal* hr__() {return VTE_TERMINAL(hr_);}

	bool api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret);
	void new_open__(const std::vector<std::string>& p, bool is_new);
	void add_end__(bool is_switch) {
		if(is_switch) init__();
	}

	bool ins_idle__(const char* s);
	void ins__(const std::string &s);

	void text_old__();
	void focus1__();
};

#endif /* VIEW_H_ */
