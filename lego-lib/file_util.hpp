/*
 * file_util.hpp
 *
 *  Created on: Jul 31, 2010
 *      Author: stephen001
 */

#ifndef LEGO_FILE_UTIL_HPP_
#define LEGO_FILE_UTIL_HPP_

template<typename T>
T get_type(std::istream & is) {
	T result = 0;
	is.read(reinterpret_cast<char *>(&result), sizeof(T));
	return result;
};

#endif /* LEGO_FILE_UTIL_HPP_ */
