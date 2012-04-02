/*
 * map.cpp
 *
 *  Created on: Jul 31, 2010
 *      Author: stephen001
 */

#include <lego/map.hpp>
#include "file_util.hpp"

bool inline overflows(const unsigned short value, const unsigned short add, const unsigned short bound ) {
	return (value + add - bound) > 0;
};

void add_map_offset(const lego::map_location & bounds, lego::map_location & loc, const unsigned char run) {
	unsigned short x_overflow = loc.x + run - bounds.x;
	if (x_overflow >= 0) {
		loc.x = x_overflow;
		if (overflows(loc.y, 1, bounds.y)) {
			loc.y = 0;
			loc.z++;
		} else {
			loc.y++;
		}
	} else {
		loc.x += run;
	};
};

namespace lego
{

bool map_location::operator==(const map_location & loc) {
	return x == loc.x && y == loc.y && z == loc.z;
};

map_location & map_location::operator=(const map_location & data) {
	if (this != &data) {
		x = data.x;
		y = data.y;
		z = data.z;
	}
	return *this;
};

bool map_reference::operator==(const map_reference & ref) {
	return turf_type_id == ref.turf_type_id && area_type_id == ref.area_type_id && initialiser_proc_id == ref.initialiser_proc_id;
};

std::istream & operator>>(std::istream & is, map_reference & data) {
	data.turf_type_id 		 = get_type<unsigned short>(is);
	data.area_type_id 		 = get_type<unsigned short>(is);
	data.initialiser_proc_id = get_type<unsigned short>(is);
	data.repeat				 = get_type<unsigned char>(is);
	return is;
};

void read_map(std::istream & is, const map_location & bounds, std::vector<map_reference> & results) {
	if (bounds.x == 0 && bounds.y == 0 && bounds.z == 0) {
		return;
	}
	unsigned int position = 0;
	unsigned int size	  = bounds.x * bounds.y *bounds.z;
	map_location loc;
	loc.x = 1;
	loc.y = 1;
	loc.z = 1;
	while (position < size) {
		map_reference ref;
		is >> ref;
		if (results.size() > 0 && ref == results[results.size() - 1]) {
			results[results.size() - 1].repeat += ref.repeat;
		} else {
			results.push_back(ref);
		}
		position += ref.repeat;
	}
}

};
