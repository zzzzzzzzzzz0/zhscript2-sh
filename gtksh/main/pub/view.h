/*
 * view.h
 *
 *  Created on: 2017年8月5日
 *      Author: zzzzzzzzzzz
 */

#ifndef PUB_VIEW_H_
#define PUB_VIEW_H_

#include "base.h"
#include "data.h"

namespace pub {

class view___ : public base___ {
private:
	bool init_ = false, init2_ = false, init2_need_ = false;
	int init2_by_ = 0;
	void init__(const char* src2);
protected:
	std::vector<std::string> init_p_;
	void reinit__();
public:
	void *window_ = nullptr, *area_ = nullptr;
	unsigned long from_ = 0;
	view___* from2_ = nullptr;

	view___() {}
	virtual ~view___() {}

	virtual GtkWidget *scrolled__() {return hr_;}

	virtual bool api__(void* shangji, const std::vector<std::string>& p, std::vector<data___>* p2, std::vector<std::string>& ret);
	virtual void new_open__(const std::vector<std::string>& p) {}
	void add_end__(const std::vector<std::string>& p);
	virtual void add_end__(bool is_switch) {init__();}
	void init__(bool and2 = true);
	void init2__(int by);
	bool has_init__() {return init_;}
	int init2_by__() {return init2_by_;}

	virtual bool is__(const std::string& name1, unsigned long id2) {return false;}
};

} /* namespace pub */

#endif /* PUB_VIEW_H_ */
