/*
 * string.cpp
 *
 *  Created on: Aug 1, 2010
 *      Author: stephen001
 */

#include <string.hpp>
#include <algorithm>
#include "file_util.hpp"

#include <iostream>

unsigned short decode_string_length(std::istream & is) {
	unsigned int    offset = is.tellg();
	unsigned short length  = get_type<unsigned short>(is);
	return length ^ offset;
};


class string_decoder {
public:
	string_decoder(unsigned int salt) {
		__position = 0;
		__salt     = salt;
	};
	unsigned char decode(unsigned char value) {
		value = value ^ (__salt + (__position * 9));
		__position++;
		return value;
	};
private:
	unsigned short __position;
	unsigned int   __salt;
};

namespace lego {

initial_string_cache::initial_string_cache(std::istream & is) {
	__block_size = get_type<unsigned int>(is);
};

const std::vector<std::string> & initial_string_cache::values() const {
	return __cache;
};

std::istream & operator>>(std::istream & is, initial_string_cache & cache) {
	unsigned short strings = get_type<unsigned short>(is);
	for (unsigned short i = 0; i < strings; i++) {
		unsigned short length = decode_string_length(is);
		string_decoder decoder(is.tellg());
		unsigned char data[length];
		is.read(reinterpret_cast<char *>(data), length);
		std::string s;
		s.reserve(length);
		for (int j = 0; j < length; j++) {
			s.push_back(decoder.decode(data[j]));
		}
		cache.__cache.push_back(s);
	}
	return is;
};

};
