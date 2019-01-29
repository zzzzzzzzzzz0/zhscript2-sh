/*
 * srcvw.cpp
 *
 *  Created on: 2017年8月27日
 *      Author: zzzzzzzzzzz
 */

#include "src.h"
#include "pub/tag.h"
#include "pub/ext.h"

static pub::tags___ tags_ = {
		{"列可语法高亮", "H", 1},
};

bool src___::api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret) {
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y':
		switch(tag[0]) {
		case 'H': {
			GtkSourceLanguageManager *slm = gtk_source_language_manager_get_default ();
			const gchar * const *ids = gtk_source_language_manager_get_language_ids (slm);
			for (int i = 0; ids[i] != NULL; i++) {
				const gchar * id = ids[i];
				GtkSourceLanguage *sl = gtk_source_language_manager_get_language (slm, id);
				if(!pub::ext_->jieshi23__(p[1].c_str(), nullptr, shangji, "lsss",
						!gtk_source_language_get_hidden (sl),
						id,
						gtk_source_language_get_name (sl),
						gtk_source_language_get_section (sl)))
					return true;
			}
			break; }
		}
		return true;
	case '<':
		pub::ext_->buzu__(p, SIZE_MAX);
		return true;
	}
	return pub::plugin___::api__(shangji, p, p2, ret);
}

static src___ plugin_;
extern "C" void *plugin__(const std::string &path) {return &plugin_;}
