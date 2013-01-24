/*
 * datum.hpp
 *
 *  Created on: Aug 1, 2010
 *      Author: stephen001
 */

#ifndef LEGO_DATUM_HPP_
#define LEGO_DATUM_HPP_

#include <istream>
#include <string>
#include <vector>

namespace lego {

struct datum_reference
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

	friend std::istream & operator>>(std::istream & is, datum_reference & ref);
};

class datum_definition
{
public:
	datum_definition(std::string & type_name);
	virtual ~datum_definition() {};
	std::string *       description();
	std::string *		name();
	std::string *		icon_state();
	datum_definition * 	parent();
	std::string	*		suffix();
	std::string	*		text_icon();
	std::string &		type_name();
	std::string &		type_path();
	void				set_description(std::string * desc);
	void				set_icon_state(std::string * state);
	void				set_name(std::string * name);
	void 				set_parent(datum_definition * parent);
	void				set_text_icon(std::string * text_icon);
	void				set_suffix(std::string * suffix);

private:
	std::string 	 *	__name;
	std::string      *   __description;
	std::string		 *	__icon_state;
	datum_definition * 	__parent;
	std::string		 *	__suffix;
	std::string		 *	__text_icon;
	std::string			__type_name;
	std::string			__type_path;
};

void read_datum_references(std::istream & is, std::vector<datum_reference> & cache);

void create_datum_definitions(std::vector<datum_reference> & references, std::vector<std::string> & strings, std::vector<datum_definition> & cache);

void resolve_datum_parents(std::vector<datum_reference> & references, std::vector<datum_definition> & cache);

};

#endif /* LEGO_DATUM_HPP_ */
