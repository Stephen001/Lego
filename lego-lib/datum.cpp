/*
 * datum.cpp
 *
 *  Created on: Aug 1, 2010
 *      Author: stephen001
 */

#include <lego/datum.hpp>
#include "file_util.hpp"
#include <functional>

#define LEGO_DATUM_USE_NEW_SPECIAL 0x0F

namespace lego
{

std::istream & operator>>(std::istream & is, datum_reference & ref) {
	ref.type_name_id 	= get_type<unsigned short>(is);
	ref.parent_type_id 	= get_type<unsigned short>(is);
	ref.name_id 		= get_type<unsigned short>(is);
	ref.description_id 	= get_type<unsigned short>(is);
	ref.icon_id 		= get_type<unsigned short>(is);
	ref.icon_state_id 	= get_type<unsigned short>(is);
	ref.direction 		= get_type<unsigned char>(is);
	ref.dm_special_type = get_type<unsigned char>(is);
	if (ref.dm_special_type == LEGO_DATUM_USE_NEW_SPECIAL) {
		ref.dm_special_type = get_type<unsigned int>(is);
	}
	ref.text_icon_id 		= get_type<unsigned short>(is);
	ref.suffix_id 			= get_type<unsigned short>(is);
	ref.flags 				= get_type<unsigned int>(is);
	ref.verb_list_id 		= get_type<unsigned short>(is);
	ref.proc_list_id 		= get_type<unsigned short>(is);
	ref.initialiser_id 		= get_type<unsigned short>(is);
	ref.initialsed_vars_id 	= get_type<unsigned short>(is);
	ref.var_list_id 		= get_type<unsigned short>(is);
	ref.layer 				= get_type<float>(is);
	ref.preset_vars_id 		= get_type<unsigned short>(is);
	return is;
};

void read_datum_references(std::istream & is, std::vector<datum_reference> & cache) {
	unsigned short length = get_type<unsigned short>(is);
	for (unsigned short i = 0; i < length; i++) {
		datum_reference ref;
		is >> ref;
		cache.push_back(ref);
	}
};

void create_datum_definitions(std::vector<datum_reference> & references, std::vector<std::string> & strings, std::vector<datum_definition> & cache) {
	for (std::vector<datum_reference>::iterator it = references.begin(); it != references.end(); it++) {
		datum_reference & ref = *it;
		std::string & type = strings[ref.type_name_id];
		datum_definition def(type);
		if (ref.name_id < 65535) {
			std::string & name = strings[ref.name_id];
			def.set_name(&name);
		}
		if (ref.description_id < 65535) {
			std::string & desc = strings[ref.description_id];
			def.set_description(&desc);
		}
		if (ref.icon_state_id < 65535) {
			std::string & icon_state = strings[ref.icon_state_id];
			def.set_icon_state(&icon_state);
		}
		cache.push_back(def);
	}
}

void resolve_datum_parents(std::vector<datum_reference> & references, std::vector<datum_definition> & cache) {
	for (unsigned int i = 0; i < references.size(); i++) {
		datum_reference & ref = references[i];
		datum_definition & me = cache[i];
		if (ref.parent_type_id < 65535) {
			datum_definition & parent = cache[ref.parent_type_id];
			me.set_parent(&parent);
		}
	}
}

datum_definition::datum_definition(std::string & type_path) : __type_path(type_path) {
	__description		  = NULL;
	__icon_state		  = NULL;
	__name 				  = NULL;
	__parent 			  = NULL;
	__suffix			  = NULL;
	__text_icon			  = NULL;
	size_t position = __type_path.find_last_of('/');
	if (position == std::string::npos) {
		__type_name = __type_path;
	} else {
		__type_name = __type_path.substr(position + 1);
	}
}

std::string * datum_definition::description() { return __description; }

std::string * datum_definition::icon_state() { return __icon_state; }

std::string * datum_definition::name() { return __name; }

datum_definition * datum_definition::parent() { return __parent; }

std::string * datum_definition::suffix() { return __suffix; }


std::string & datum_definition::type_name() { return __type_name; }

std::string & datum_definition::type_path() { return __type_path; }

void datum_definition::set_description(std::string * desc) { this->__description = desc; }

void datum_definition::set_icon_state(std::string * state) { this->__icon_state = state; }

void datum_definition::set_name(std::string * name) { this->__name = name; }

void datum_definition::set_parent(datum_definition * parent) { this->__parent = parent; }

void datum_definition::set_suffix(std::string * suffix) { this->__suffix = suffix; }

void datum_definition::set_text_icon(std::string * text_icon) { this->__text_icon = text_icon; }

};
