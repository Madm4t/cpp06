#include <iostream>
#include "Base.hpp"

int main(void) {
	Base* obj = generate();
	identify(obj);
	identify(*obj);
	delete obj;
}