/*
 * binary_chunk.cpp
 *
 *  Created on: Aug 1, 2010
 *      Author: stephen001
 */

#include <binary_chunk.hpp>
#include <cstring>
#include "file_util.hpp"

namespace lego
{

binary_chunk::binary_chunk(std::istream & is) : size(get_type<unsigned short>(is) * 2), data(new unsigned char[size]) {};

binary_chunk::binary_chunk(const binary_chunk & copy) : size(copy.size), data(new unsigned char[size]) {
	std::memcpy(data, copy.data, size);
}

void binary_chunk::read(std::istream & is) {
	is.read(reinterpret_cast<char *>(data), size);
}

binary_chunk::~binary_chunk() {
	delete data;
};

void read_binary_chunks(std::istream & is, std::vector<binary_chunk> & cache) {
	unsigned short length = get_type<unsigned short>(is);
	for (unsigned short i = 0; i < length; i++) {
		binary_chunk c(is);
		c.read(is);
		cache.push_back(c);
	};
};

};
