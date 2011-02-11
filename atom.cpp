/*
 * atom.cpp
 *
 *  Created on: Aug 1, 2010
 *      Author: stephen001
 */

#include <atom.hpp>
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

};
