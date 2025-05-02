#include "ScalarConverter.hpp"
#include <iostream>

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "Use: ./convert <type>\n";
		return 1;
	}
	std::string literal = argv[1];
	ScalarConverter::convert(literal);
	return 0;
};