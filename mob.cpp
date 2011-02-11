/*
 * mob.cpp
 *
 *  Created on: Aug 1, 2010
 *      Author: stephen001
 */

#include <mob.hpp>
#include "file_util.hpp"

#define LEGO_MOB_EXTENDED_SIGHT_RULES 0x80

namespace lego {

std::istream & operator>>(std::istream & is, mob_reference & ref) {
	ref.atom_type_id 	= get_type<unsigned short>(is);
	ref.key_id			= get_type<unsigned short>(is);
	ref.sight_flags     = get_type<unsigned char>(is);
	if (ref.sight_flags & LEGO_MOB_EXTENDED_SIGHT_RULES) {
		ref.sight_flags 	= get_type<unsigned int>(is);
		ref.see_in_dark 	= get_type<unsigned char>(is);
		ref.see_invisible 	= get_type<unsigned char>(is);
	} else {
		ref.see_in_dark = 2;
		ref.see_invisible = ref.sight_flags & 0x02 ? 1 : 0;
		ref.sight_flags = 0;
	}
	return is;
};

void read_mob_references(std::istream & is, std::vector<mob_reference> & cache) {
	unsigned short length = get_type<unsigned short>(is);
	for (unsigned short i = 0; i < length; i++) {
		mob_reference ref;
		is >> ref;
		cache.push_back(ref);
	}
};

};
