/*
 * print-info.cpp
 *
 *  Created on: Apr 2, 2012
 *      Author: badgers
 */

#include <iostream>
#include <fstream>

#include <lego/map.hpp>
#include <lego/version.hpp>

#include "includes.hpp"

void print_info(char * name) {
	std::ifstream stream(name, std::ios::in|std::ios::binary);
	lego::dmb_metadata data;
	data.compiled_version 	= 0;
	data.min_version 		= 0;
	stream >> data;
	std::cout << "DMB File: " << name << "" << std::endl << std::endl;
	std::cout << "Compiled version = " << data.compiled_version << std::endl;
	std::cout << "Min Comp version = " << data.min_version << std::endl;
	lego::map_location map_size;
	stream >> map_size;
	std::cout << std::endl << "Map size:" << std::endl;
	std::cout << "X = " << map_size.x << std::endl;
	std::cout << "Y = " << map_size.y << std::endl;
	std::cout << "Z = " << map_size.z << std::endl;
}
