/*
 * l4.h
 *
 *  Created on: 2017年8月4日
 *      Author: zzzzzzzzzzz
 */

#ifndef L4_H_
#define L4_H_

#include "pub2/l4.h"

class l4___ : public pub2::l4___ {
private:
	bool path__(const char* path, std::string &path3, std::string &path1, std::string &path11);
public:
	std::string path_;
	l4___();
	virtual ~l4___();
	bool init2__(const char* line, int argc, char* argv[], std::string &path1);
};

extern bool exists__(const char *filename);
extern bool is_symlink__(const char *filename);
extern bool realpath__(std::string &path);
extern bool realpath2__(std::string &path);

#endif /* L4_H_ */
