/*
 * print-info.cpp
 *
 *  Created on: Apr 2, 2012
 *      Author: badgers
 */

#include <iostream>
#include <fstream>
#include <vector>

#include <lego/atom.hpp>
#include <lego/map.hpp>
#include <lego/mob.hpp>
#include <lego/string.hpp>
#include <lego/version.hpp>

#include "includes.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

void print_info(char * name) {
#ifdef _WIN32
	LARGE_INTEGER t;
	double frequency = 0;
	QueryPerformanceFrequency(&t);
	frequency = double(t.QuadPart) / 1000.0;
	QueryPerformanceCounter(&t);
	LONGLONG start = t.QuadPart;
#endif
	std::ifstream stream(name, std::ios::in|std::ios::binary);
	lego::dmb_metadata data;
	data.compiled_version 	= 0;
	data.min_version 		= 0;
	stream >> data;
	lego::map_location map_size;
	stream >> map_size;
	if (map_size.z > 0) {
		std::vector<lego::map_reference> map_references;
		lego::read_map(stream, map_size, map_references);
	}
	lego::initial_string_cache string_cache(stream);
	std::vector<lego::atom_reference> atom_references;
	lego::read_atom_references(stream, atom_references);
	std::vector<lego::mob_reference> mob_references;
	lego::read_mob_references(stream, mob_references);
	stream >> string_cache;
#ifdef _WIN32
	QueryPerformanceCounter(&t);
	LONGLONG end = t.QuadPart;
	std::cout << "Reading DMB took " << (end - start) / frequency << "ms" << std::endl;
#endif
	std::cout << "DMB File: " << name << "" << std::endl << std::endl;
	std::cout << "Compiled version = " << data.compiled_version << std::endl;
	std::cout << "Min Comp version = " << data.min_version << std::endl;
	std::cout << std::endl << "Map size:" << std::endl;
	std::cout << "X = " << map_size.x << std::endl;
	std::cout << "Y = " << map_size.y << std::endl;
	std::cout << "Z = " << map_size.z << std::endl;
	std::cout << std::endl << "Code size:" << std::endl;
	std::cout << "Distinct atom definitions  = " << atom_references.size() << std::endl;
	std::cout << "Distinct mob definitions   = " << mob_references.size() << std::endl;
	std::cout << "Distinct names and strings = " << string_cache.values().size() << std::endl;
}
