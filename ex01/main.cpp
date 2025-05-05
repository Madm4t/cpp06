#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

int main(void) {
	Data original{"Heilbronn", 42};

	std::cout
		<< "original adress: "
		<< &original
		<< "\noriginal values: "
		<< original.name << " "
		<< original.value
		<< std::endl;
	
	std::uintptr_t serialized = Serializer::serialize(&original);

	std::cout
		<< "raw value: "
		<< serialized << std::endl;

	Data* deserialized = Serializer::deserialize(serialized);

	std::cout
		<< "deserialized adress: "
		<< deserialized
		<< "\ndeserialized values: "
		<< deserialized->name  << " "
		<< deserialized->value
		<< std::endl;

	if (&original == deserialized) {
		std::cout << "adresses are equal\n";
	}
	return (0);
}