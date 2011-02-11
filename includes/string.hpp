/*
 * string.hpp
 *
 *  Created on: Jul 31, 2010
 *      Author: stephen001
 */

#ifndef LEGO_STRING_HPP_
#define LEGO_STRING_HPP_

#include <istream>
#include <string>
#include <vector>

namespace lego {

class initial_string_cache {
public:
	initial_string_cache(std::istream & is);
	~initial_string_cache() {};
	const std::vector<std::string> & values() const;
	friend std::istream & operator>>(std::istream & is, initial_string_cache & cache);
private:
	unsigned int __block_size;
	std::vector<std::string> __cache;
};

};

#endif /* LEGO_STRING_HPP_ */
