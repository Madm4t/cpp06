#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"


Base::~Base() {
	std::cout << "Base deconstructor called.\n";
}

Base* generate(void) {
	std::srand(std::time(nullptr));

	int randNum = std::rand() % 3;
	if (randNum == 0) {
		return new A;
	}
	else if (randNum == 1) {
		return new B;
	}
	else {
		return new C;
	}
}

void identify(Base *p) {
	if (dynamic_cast<A*>(p))
		std::cout << "A\n";
	else if (dynamic_cast<B*>(p))
		std::cout << "B\n";
	else if (dynamic_cast<C*>(p))
		std::cout << "C\n";
	else
		std::cout << "Unkown class\n";
}

void identify(Base& p) {
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "A\n";
	}
	catch (std::bad_cast&) {
		try {
			(void)dynamic_cast<B&>(p);
			std::cout << "B\n";
		}
		catch (std::bad_cast&) {
			try {
				(void)dynamic_cast<C&>(p);
				std::cout << "C\n";
			}
			catch (std::bad_cast&) {
				std::cout << "Unknown type\n";
			}

		}
	}
}