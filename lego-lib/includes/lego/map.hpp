/*
 * map.hpp
 *
 *  Created on: Jul 31, 2010
 *      Author: stephen001
 */

#ifndef MAP_HPP_
#define MAP_HPP_

#include <istream>
#include <vector>

#define LEGO_NO_INITIALISER_PROC 0xFFFF

namespace lego
{

struct map_location {
	unsigned short x;
	unsigned short y;
	unsigned short z;

	bool operator==(const map_location & loc);
	map_location & operator=(const map_location & data);
	friend std::istream & operator>>(std::istream & is, map_location & data);
};

struct map_reference {
	unsigned short turf_type_id;
	unsigned short area_type_id;
	unsigned short initialiser_proc_id;
	unsigned int repeat;
	map_location starting_location;

	bool operator==(const map_reference & ref);
	friend std::istream & operator>>(std::istream & is, map_reference & data);
};

void read_map(std::istream & is, const map_location & bounds, std::vector<map_reference> & results);
};


#endif /* MAP_HPP_ */
