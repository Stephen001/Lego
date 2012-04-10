/*
 * atom.cpp
 *
 *  Created on: Aug 1, 2010
 *      Author: stephen001
 */

#include <lego/atom.hpp>
#include "file_util.hpp"

#define LEGO_ATOM_USE_NEW_SPECIAL 0x0F

namespace lego
{

std::istream & operator>>(std::istream & is, atom_reference & ref) {
	ref.type_name_id 	= get_type<unsigned short>(is);
	ref.parent_type_id 	= get_type<unsigned short>(is);
	ref.name_id 		= get_type<unsigned short>(is);
	ref.description_id 	= get_type<unsigned short>(is);
	ref.icon_id 		= get_type<unsigned short>(is);
	ref.icon_state_id 	= get_type<unsigned short>(is);
	ref.direction 		= get_type<unsigned char>(is);
	ref.dm_special_type = get_type<unsigned char>(is);
	if (ref.dm_special_type == LEGO_ATOM_USE_NEW_SPECIAL) {
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

void read_atom_references(std::istream & is, std::vector<atom_reference> & cache) {
	unsigned short length = get_type<unsigned short>(is);
	for (unsigned short i = 0; i < length; i++) {
		atom_reference ref;
		is >> ref;
		cache.push_back(ref);
	}
};

void create_atom_definitions(std::vector<atom_reference> & references, std::vector<std::string> & strings, std::vector<atom_definition> & cache) {
	for (std::vector<atom_reference>::iterator it = references.begin(); it != references.end(); it++) {
		atom_reference & ref = *it;
		std::string & type = strings[ref.type_name_id];
		atom_definition def(type);
		if (ref.name_id < 65535) {
			std::string & name = strings[ref.name_id];
			def.set_name(&name);
		}
		cache.push_back(def);
	}
}

void resolve_atom_parents(std::vector<atom_reference> & references, std::vector<atom_definition> & cache) {
	for (unsigned int i = 0; i < references.size(); i++) {
		atom_reference & ref = references[i];
		atom_definition & me = cache[i];
		if (ref.parent_type_id < 65535) {
			atom_definition & parent = cache[ref.parent_type_id];
			me.set_parent(&parent);
		}
	}
}

atom_definition::atom_definition(std::string & type_path) : __type_path(type_path) {
	__name 				  = NULL;
	__parent 			  = NULL;
	size_t position = __type_path.find_last_of('/');
	if (position == std::string::npos) {
		__type_name = __type_path;
	} else {
		__type_name = __type_path.substr(position + 1);
	}
}

std::string * atom_definition::name() {
	return __name;
}

atom_definition * atom_definition::parent() { return __parent; }

std::string & atom_definition::type_name() { return __type_name; }

std::string & atom_definition::type_path() { return __type_path; }

void atom_definition::set_name(std::string * name) { this->__name = name; }

void atom_definition::set_parent(atom_definition * parent) { this->__parent = parent; }

};
