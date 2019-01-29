/*
 * ext.cpp
 *
 *  Created on: 2017年8月7日
 *      Author: zzzzzzzzzzz
 */

#include "ext.h"
#include "sig.h"

namespace pub {

static bool push_end__(const char* argc, va_list &argv, ext___ *ext, std::vector<std::string> &p) {
	if(argc) {
		int n = 0;
		auto nxx = [&]() {
			for(int i = 0; i < n; i++)
				p.push_back(null_);
			n = 0;
		};
		for(int i = 0;; i++) {
			char typ = argc[i];
			if(!typ)
				break;
			if(typ != 's')
				nxx();
			switch(typ) {
			case 's': {
				char* s = va_arg(argv, char*);
				if(s) {
					nxx();
					p.push_back(s);
				} else
					n++;
				break; }
			case 'i': p.push_back(std::to_string(va_arg(argv, int))); break;
			case 'I': p.push_back(std::to_string(va_arg(argv, unsigned int))); break;
			case 'l': p.push_back(std::to_string(va_arg(argv, long))); break;
			case 'L': p.push_back(std::to_string(va_arg(argv, unsigned long))); break;
			//‘float’ is promoted to ‘double’ when passed through ‘...’
			case 'f': //p.push_back(std::to_string(va_arg(argv, float))); break;
			case 'd': p.push_back(std::to_string(va_arg(argv, double))); break;
			case 'p': p.push_back(std::to_string((unsigned long)va_arg(argv, void*))); break;
			case '#': {
				view___* v = va_arg(argv, view___*);
				ext->push__(v, "#", p);
				break; }
			default:
				return false;
			}
		}
	}
	va_end(argv);
	return true;
}

bool ext___::jieshi2__(pub::view___ *v, const char* src2, const char* argc,...) {
	std::vector<std::string> p;
	va_list argv;
	va_start(argv, argc);
	if(!push_end__(argc, argv, this, p)) {
		err__(argc);
		return false;
	}
	return jieshi__(nullptr, v, nullptr, src2, nullptr, false, &p, nullptr, nullptr);
}
bool ext___::jieshi21__(void* w, const char* src2, const char* argc,...) {
	std::vector<std::string> p;
	va_list argv;
	va_start(argv, argc);
	if(!push_end__(argc, argv, this, p)) {
		err__(argc);
		return false;
	}
	return jieshi__(w, nullptr, nullptr, src2, nullptr, false, &p, nullptr, nullptr);
}
bool ext___::jieshi23__(const char* src, const char* src2, void* shangji, const char* argc,...) {
	std::vector<std::string> p;
	va_list argv;
	va_start(argv, argc);
	if(!push_end__(argc, argv, this, p)) {
		err__(argc);
		return false;
	}
	return jieshi__(nullptr, nullptr, src, src2, shangji, false, &p, nullptr, nullptr);
}
bool ext___::jieshi22__(void* user_data, const char* argc,...) {
	sign___* sign = (sign___*)user_data;
	std::vector<std::string> p;
	va_list argv;
	va_start(argv, argc);
	if(!push_end__(argc, argv, this, p)) {
		err__(argc);
		return false;
	}
	return jieshi__(nullptr, (view___*)sign->data_,
			sign->code_.empty() ? nullptr : sign->code_.c_str(),
			sign->sig_name_.c_str(), nullptr, false, &p, nullptr, nullptr);
}

ext___* ext_ = nullptr;

} /* namespace pub */
