/*
 * atom.hpp
 *
 *  Created on: Aug 1, 2010
 *      Author: stephen001
 */

#ifndef LEGO_ATOM_HPP_
#define LEGO_ATOM_HPP_

#include <istream>
#include <vector>

#define LEGO_ATOM_NONE

namespace lego {

struct atom_reference
{
	unsigned short type_name_id;
	unsigned short parent_type_id;
	unsigned short name_id;
	unsigned short description_id;
	unsigned short icon_id;
	unsigned short icon_state_id;
	unsigned char  direction;
	unsigned int   dm_special_type;
	unsigned short text_icon_id;
	unsigned short suffix_id;
	unsigned int   flags;
	unsigned short verb_list_id;
	unsigned short proc_list_id;
	unsigned short initialiser_id;
	unsigned short initialsed_vars_id;
	unsigned short var_list_id;
	float		   layer;
	unsigned short preset_vars_id;

	friend std::istream & operator>>(std::istream & is, atom_reference & ref);
};

void read_atom_references(std::istream & is, std::vector<atom_reference> & cache);

};

#endif /* LEGO_ATOM_HPP_ */
