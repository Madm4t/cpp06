#include <string>
#include <iostream>

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		std::string literal = argv[1];
		std::size_t position = 0;
		while ((position = literal.find("f", position)) != std::string::npos) {
			std::cout << "string was found at position : " << position << std::endl;
			position++;
		}
	}
	else
		std::cout << "Proide exactly one parameter\n";
	return 0;
}