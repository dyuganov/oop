
#include <iostream>
#include <exception>

#include "Map.h"
#include "View.h"
#include "Explorer.h"

using namespace std;

int main(int argc, char* argv[]) {
	/*
	Map m;

	for (size_t i = 0; i < 30; ++i) {
		for (size_t j = 0; j < 30; ++j) {
			std::cout << char(m.getMap()[i][j]) << ' ';
		}
		std::cout << std::endl;
	}
	*/
	try {
		
	}
	catch (std::exception& e) {
		std::cout << "Some problems: " << e.what() << std::endl;
	}

	return 0;
}