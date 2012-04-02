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

class resource {
public:
	resource() {};
	~resource() {};
	const std::string & get_name() const { return name; };
	unsigned int  		get_size() const { return size; };
	void write(std::string & directory) const;

	friend std::istream & operator>>(std::istream & is, resource & ref);
private:
	std::string		name;
	unsigned char * data;
	unsigned int	size;
};

void read_resources(std::istream & is, std::vector<resource> & resources);

};

#endif /* LEGO_RESOURCE_HPP_ */
