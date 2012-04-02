/*
 * version.hpp
 *
 *  Created on: Jul 31, 2010
 *      Author: stephen001
 */

#ifndef LEGO_VERSION_HPP_
#define LEGO_VERSION_HPP_

#include <istream>

#define LEGO_LOOPCHECKS_DISABLED 0x02

namespace lego
{

struct dmb_metadata {
	unsigned short compiled_version;
	unsigned short min_version;
	unsigned int   flags;

	friend std::istream & operator>>(std::istream & is, dmb_metadata & data);
};

};

#endif /* LEGO_VERSION_HPP_ */
