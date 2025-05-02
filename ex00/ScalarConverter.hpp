#pragma once

#include <string>

class ScalarConverter {
private:
	ScalarConverter() = delete;
	~ScalarConverter() = delete;
	ScalarConverter(const ScalarConverter&) = delete;
	ScalarConverter& operator=(const ScalarConverter&) = delete;

public:
	static void convert(const std::string& literal);
};

enum literalType {
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	PSEUDO_FLOAT,
	PSEUDO_DOUBLE,
	UNKNOWN
};
