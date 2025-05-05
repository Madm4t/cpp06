#pragma once

#include <cstdint>

struct Data;

class Serializer {
private:
	Serializer() = delete;
	~Serializer() = delete;
	Serializer(const Serializer&) = delete;
	Serializer& operator=(const Serializer&) = delete;

public:
	static std::uintptr_t serialize(Data* ptr);
	static Data* deserialize(std::uintptr_t raw);
};
