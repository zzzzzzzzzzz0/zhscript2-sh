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
public:
	bool init_ = false;

	view___();
	virtual ~view___();

	GtkWidget *scrolled__() {return box_;}
	VteTerminal* hr__() {return VTE_TERMINAL(hr_);}

	bool api__(void* shangji, const std::vector<std::string>& p, std::vector<std::string>& ret);
	void new_open__(const std::vector<std::string>& p);
};

#endif /* VIEW_H_ */
