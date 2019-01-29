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
	GPid pid_ = 0;

	bool cmd1_ = false, ins1_ = true;
public:
	std::string title_, data_;

	view___();
	virtual ~view___();

	GtkWidget *scrolled__() {return box_;}
	VteTerminal* hr__() {return VTE_TERMINAL(hr_);}

	bool api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret);
	void new_open__(const std::vector<std::string>& p);
	void add_end__(bool is_switch) {
		if(is_switch) init__();
	}

	bool ins_init__(const char* s);
	void ins__(const std::string &s);
};

#endif /* VIEW_H_ */
