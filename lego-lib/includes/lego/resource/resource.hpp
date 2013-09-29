/*
 * resource.hpp
 *
 *  Created on: Dec 14, 2010
 *      Author: stephen001
 */

#ifndef LEGO_RESOURCE_HPP_
#define LEGO_RESOURCE_HPP_

#include <istream>
#include <string>
#include <vector>

namespace lego
{

struct resource {
	std::string	  * name;
	char 		  * data;
	unsigned int	size;
	bool			active;

	friend std::istream & operator>>(std::istream & is, resource & ref);
};

void read_resources(std::istream & is, std::vector<resource> & resources);

void write_resource(resource & res, std::string & directory);

};

#endif /* LEGO_RESOURCE_HPP_ */
