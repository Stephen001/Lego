/*
 * write-resources.cpp
 *
 *  Created on: 24 Jan 2013
 *      Author: Stephen
 */

#include <iostream>
#include <fstream>
#include <vector>

#include <lego/resource/resource.hpp>

#include "includes.hpp"


void write_resources(char * name, char * directory) {
	std::ifstream stream(name, std::ios::in|std::ios::binary);
	std::string dir(directory);
	std::vector<lego::resource> resources;
	lego::read_resources(stream, resources);
	for (std::vector<lego::resource>::iterator it = resources.begin(); it != resources.end(); it++) {
		lego::resource & res = (*it);
		std::cout << "Found " << *(res.name) << " size " << res.size << std::endl;
		lego::write_resource(res, dir);
	}
}
