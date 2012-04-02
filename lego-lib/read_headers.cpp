/*
 * read_version.cpp
 *
 *  Created on: Jul 31, 2010
 *      Author: stephen001
 */

#include <lego/map.hpp>
#include <lego/version.hpp>
#include "file_util.hpp"
#include <sstream>
#include <string>

unsigned short read_three_digits_as_string(std::istream & is) {
	char number[3] = {};
	is.read(number, 3);
	std::stringstream ss(std::string(number), std::ios_base::in);
	unsigned short result;
	ss >> result;
	return result;
};

namespace lego
{

std::istream & operator>>(std::istream & is, lego::map_location & data) {
	data.x = get_type<unsigned short>(is);
	data.y = get_type<unsigned short>(is);;
	data.z = get_type<unsigned short>(is);;
	return is;
};

std::istream & operator>>(std::istream & is, lego::dmb_metadata & data) {
	is.ignore(11);
	data.compiled_version = read_three_digits_as_string(is);
	is.ignore(20);
	data.min_version = read_three_digits_as_string(is);
	is.ignore(5);
	data.flags = get_type<unsigned int>(is);
	return is;
};

};
