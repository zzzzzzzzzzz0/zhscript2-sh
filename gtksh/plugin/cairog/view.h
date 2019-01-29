/*
 * view.h
 *
 *  Created on: 2018年01月21日
 *      Author: zzzzzzzzzzz
 */

#ifndef VIEW_H_
#define VIEW_H_

#include "pub/view.h"

class view___: public pub::view___ {
private:
	bool draw_code__(const std::vector<std::string>& p, size_t i);
public:
	std::string draw_code_;
	bool draw_code_ok_ = false;

	view___();
	virtual ~view___();

	bool api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret);
	void new_open__(const std::vector<std::string>& p);
};

#endif /* VIEW_H_ */
