/*
 * mob.hpp
 *
 *  Created on: Aug 1, 2010
 *      Author: stephen001
 */

#ifndef LEGO_MOB_HPP_
#define LEGO_MOB_HPP_

#include <istream>
#include <vector>

namespace lego
{

struct mob_reference {
	unsigned short atom_type_id;
	unsigned short key_id;
	unsigned int   sight_flags;
	unsigned char  see_in_dark;
	unsigned char  see_invisible;

	friend std::istream & operator>>(std::istream & is, mob_reference & ref);
};

void read_mob_references(std::istream & is, std::vector<mob_reference> & cache);

};


#endif /* LEGO_MOB_HPP_ */
