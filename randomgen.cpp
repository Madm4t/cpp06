#include <iostream>
#include <cstdlib>
#include <ctime>

int main(void) {
	std::srand(std::time(nullptr));

	int randomNum = std::rand() % 3;
	if (randomNum == 0)
		std::cout << randomNum << std::endl;
	if (randomNum == 1)
		std::cout << randomNum << std::endl;
	if (randomNum == 2)
		std::cout << randomNum << std::endl;

	return (0);
}