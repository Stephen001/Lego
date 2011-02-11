/*
 * binary_chunks.hpp
 *
 *  Created on: Aug 1, 2010
 *      Author: stephen001
 */

#ifndef LEGO_BINARY_CHUNK_HPP_
#define LEGO_BINARY_CHUNK_HPP_

#include <istream>
#include <vector>

namespace lego
{

struct binary_chunk {
	binary_chunk(std::istream & is);
	binary_chunk(const binary_chunk & copy);
	void read(std::istream & is);
	~binary_chunk();
	unsigned short size;
	unsigned char * data;
};

void read_binary_chunks(std::istream & is, std::vector<binary_chunk> & cache);

};

#endif /* LEGO_BINARY_CHUNK_HPP_ */
