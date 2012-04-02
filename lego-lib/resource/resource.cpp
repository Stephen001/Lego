/*
 * resource.cpp
 *
 *  Created on: Dec 14, 2010
 *      Author: stephen001
 */

#include <lego/resource/resource.hpp>
#include "../file_util.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>

namespace lego
{

std::istream & operator>>(std::istream & is, resource & ref) {
	if (is.good()) {
		is.ignore(18);
		int size = get_type<int>(is);
		ref.data = new unsigned char[size];
		std::vector<char> characters;
		char c = is.get();
		while ( c != '\0' && c != -1 ) {
			characters.push_back(c);
			c = is.get();
		}
		if ( c == -1 ) {
			is.setstate(std::ios::eofbit);
			return is;
		}
		characters.push_back(c);
		ref.name = std::string(characters.begin(), characters.end());
		is.read(reinterpret_cast<char *>(ref.data), size);
		ref.size = size;
	} else {
		is.setstate(std::ios::eofbit);
	}
	return is;
}

void resource::write(std::string & directory) const {
	std::string temp(directory);
	temp.append("/").append(name);
	std::ofstream stream(temp.c_str());
	stream.write(reinterpret_cast<char *>(data), size);
	stream.close();
}

void read_resources(std::istream & is, std::vector<resource> & resources) {
	std::istream_iterator<resource> begin(is), end;
	std::copy(begin, end, std::back_inserter(resources));
}

};
