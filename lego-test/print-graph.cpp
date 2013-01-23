/*
 * print-graph.cpp
 *
 *  Created on: Apr 10, 2012
 *      Author: badgers
 */

#include <iostream>
#include <fstream>
#include <vector>

#include <lego/datum.hpp>
#include <lego/map.hpp>
#include <lego/mob.hpp>
#include <lego/string.hpp>
#include <lego/version.hpp>

#include "includes.hpp"

void print_graph(char * name) {
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
	std::vector<lego::datum_reference> datum_references;
	lego::read_datum_references(stream, datum_references);
	std::vector<lego::mob_reference> mob_references;
	lego::read_mob_references(stream, mob_references);
	stream >> string_cache;
	std::vector<lego::datum_definition> definitions;
	std::vector<std::string> & strings = const_cast<std::vector<std::string> &>(string_cache.values());
	lego::create_datum_definitions(datum_references, strings, definitions);
	lego::resolve_datum_parents(datum_references, definitions);
	std::cout << "digraph objtree {" << std::endl;
	for (std::vector<lego::datum_definition>::iterator it = definitions.begin(); it != definitions.end(); it++) {
		lego::datum_definition & def = *it;
		std::cout << "\t";
		if (def.parent() != NULL) {
			std::cout << def.parent()->type_name() << " -> ";
		} else {
			std::cout << "root" << " -> ";
		}
		std::cout << def.type_name() << ";" << std::endl;
	}
	std::cout << "}" << std::endl;
}

