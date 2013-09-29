/*
 * resource.cpp
 *
 *  Created on: Dec 14, 2010
 *      Author: stephen001
 */

#include <lego/resource/resource.hpp>
#include "../file_util.hpp"
#include <algorithm>
#include <cstring>
#include <iterator>
#include <fstream>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif



namespace lego
{

const char get_directory_separator() {
#ifdef _WIN32
	return '\\';
#else
	return '/';
#endif
}

const std::vector<std::string> explode(const std::string & str, const char & ch) {
	std::string next;
	std::vector<std::string> result;

    for (std::string::const_iterator it = str.begin(); it != str.end(); it++) {
        if (*it == ch) {
            if (!next.empty()) {
                result.push_back(next);
                next.clear();
            }
        } else {
            next += *it;
        }
    }
    if (!next.empty()) {
         result.push_back(next);
    }
    return result;
}

void create_directory(std::string & directory) {
#ifdef _WIN32
	CreateDirectory(directory.c_str(), NULL);
#else
	mkdir(directory.c_str(), S_IRWXU|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
#endif
}

std::istream & operator>>(std::istream & is, resource & ref) {
	unsigned int blockSize = get_type<unsigned int>(is);
	unsigned char isActive = is.get();
	if (isActive == 1) {
		ref.active = true;
		is.ignore(13);
		unsigned int size = get_type<unsigned int>(is);
		ref.data = new char[size == 0 ? 1 : size];
		memset(ref.data, 0, size);
		std::vector<char> characters;
		char c = is.get();
		while (c != '\0' && c != -1) {
			characters.push_back(c);
			c = is.get();
		}
		characters.push_back(c);
		ref.name = new std::string(characters.begin(), characters.end());
		if (size > 0) {
			is.read(ref.data, size);
		}
		ref.size = size;
	} else {
		ref.active = false;
		ref.size = blockSize;
		is.ignore(blockSize);
	}
	return is;
}

void write_resource(resource & res, std::string & directory) {
	std::string temp(directory);
	create_directory(directory);
	const char sep = get_directory_separator();
	char sepTotal[] = {sep, '\0'};
	const std::vector<std::string> & parts = explode(*(res.name), sep);
	for (std::vector<std::string>::const_iterator it = parts.begin(); it != parts.end(); it++) {
		temp.append(sepTotal).append(*it);
		if (*it != parts.back()) {
			create_directory(temp);
		}
	}
	std::ofstream stream(temp.c_str(), std::ios::out|std::ios::binary|std::ios::trunc);
	stream.write(res.data, res.size);
	stream.close();
}

void read_resources(std::istream & is, std::vector<resource> & resources) {
	while (is.good()) {
		resource res;
		is >> res;
		resources.push_back(res);
	}
}

};
