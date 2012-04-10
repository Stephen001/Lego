/*
 * main.cpp
 *
 *  Created on: Apr 2, 2012
 *      Author: badgers
 */

#include <string>

#include "includes.hpp"

int main(int argc, char ** argv) {
	std::string command(argv[1]);
	if (command.compare("print-info") == 0) {
		print_info(argv[2]);
	}
	if (command.compare("print-graph") == 0) {
			print_graph(argv[2]);
		}
	return 0;
}
