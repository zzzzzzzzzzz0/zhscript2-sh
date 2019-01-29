/*
 * addopt.h
 *
 *  Created on: 2017年11月22日
 *      Author: zzzzzzzzzzz
 */

#ifndef PUB_ADDOPT_H_
#define PUB_ADDOPT_H_

#include <string>

namespace pub {

class add_opt___ {
public:
	char typ_ = 0, typ2_ = 0;
	bool new_window_ = false, is_app_paintable_ = false;
	bool to_ = true, has_button_ = true, can_close_ = true;
	char pos_ = 'c';
	int w_req_ = -1, h_req_ = -1;
	std::string name_, window_name_;
	unsigned long from_ = 0, id_ = 0;
	std::string code_;
	bool first_no_ = false, down_ = false, no_focus_ = false,
			append_ = false, insert0_ = false,
			only_switch_ = false, use_open_ = true,
			is_set_typ_ = false,
			is_set_to_ = false,
			is_set_has_button_ = false,
			is_set_can_close_ = false,
			is_set_pos_ = false;

	void copy__(const add_opt___* opt) {
		typ_ = opt->typ_;
		typ2_ = opt->typ2_;
		can_close_ = opt->can_close_;
		has_button_ = opt->has_button_;
		to_ = opt->to_;
		pos_ = opt->pos_;
		first_no_ = opt->first_no_;
		append_ = opt->append_;
	}
};

} /* namespace pub */

#endif /* PUB_ADDOPT_H_ */
