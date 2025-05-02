#include "ScalarConverter.hpp"
#include <cctype>
#include <iostream>
//stoi() convert string to int (used since c++11), atoi() is (C-Style)
//stof() or atof() convert string to float
//stod() convert string to double

static literalType detectType(const std::string& literal);

void ScalarConverter::convert(const std::string& literal)
{
	char	c = 0;
	int		i = 0;
	double	d = 0.0;
	float	f = 0.0f;
	std::string pseudod = NULL;
	std::string pseudof = NULL;

	literalType type = detectType(literal);
	switch (type) {
	case CHAR:
		c = literal[0];
		d = static_cast<int>(c);
		f = static_cast<float>(c);
		d = static_cast<double>(c);
		break;
	case INT:
		try {
			i = std::stoi(literal);
		}
		catch (std::out_of_range& e) {
			std::cout << "char: invalid literal, int is out of range\n";
			std::cout << "int: invalid literal, int is out of range\n";
			std::cout << "flaot: invalid literal, int is out of range\n";
			std::cout << "double: invalid literal, int is out of range\n";
			return;
		}
		catch (...) {
			std::cout << "char: Non discplayable\n";
		}
		c = static_cast<char>(i);
		f = static_cast<float>(i);
		d = static_cast<double>(i);
		break;
	case FLOAT:
		try {
			f = std::stof(literal);
		}
		catch (std::out_of_range& e) {
			std::cout << "char: invalid literal, float is out of range\n";
			std::cout << "int: invalid literal, float is out of range\n";
			std::cout << "flaot: invalid literal, float is out of range\n";
			std::cout << "double: invalid literal, float is out of range\n";
			return;
		}
		catch (...) {
			std::cout << "float: invalid literal\n";
		}
		c = static_cast<char>(f);
		i = static_cast<int>(f);
		d = static_cast<double>(f);
		break;
	case DOUBLE:
		try {
			f = std::stod(literal);
		}
		catch (std::out_of_range& e) {
			std::cout << "char: invalid literal, double is out of range\n";
			std::cout << "int: invalid literal, double is out of range\n";
			std::cout << "flaot: invalid literal, double is out of range\n";
			std::cout << "double: invalid literal, double is out of range\n";
			return;
		}
		catch (...) {
			std::cout << "double: invalid literal\n";
		}
		c = static_cast<char>(d);
		i = static_cast<int>(d);
		f = static_cast<float>(d);
		break;
	case PSEUDO_FLOAT:
		pseudod = literal;
		pseudod.pop_back();
		std::cout << "char: impossible\n";
		std::cout << "int: impossible\n";
		std::cout << "flaot: " << literal << "\n";
		std::cout << "double: " << pseudod << "\n";
		return;
	case PSEUDO_DOUBLE:
		pseudof = literal + 'f';
		std::cout << "char: impossible\n";
		std::cout << "int: impossible\n";
		std::cout << "flaot: " << pseudof << "\n";
		std::cout << "double: " << literal << "\n";
		return;
	case UNKNOWN:
		std::cout << "Input is invalid, use: char, int, float or double \n";
		std::cout << "char: impossible\n";
		std::cout << "int: impossible\n";
		std::cout << "float: impossible\n";
		std::cout << "double: impossible\n";
		return;
	}
}

static literalType detectType(const std::string& literal) {
	//check Pseudo literals
	if (literal == "nanf" || literal == "+inff" || literal == "-inff")
		return PSEUDO_FLOAT;
	if (literal == "nan" || literal == "+inf" || literal == "-inf")
		return PSEUDO_DOUBLE;
	//check if char
	if (literal.size() == 1 &&
		!std::isdigit(static_cast<unsigned char>(literal[0])) &&
		std::isprint(static_cast<unsigned char>(literal[0])))
		return CHAR;
	//check if float
	if (literal.back() == 'f')
		return FLOAT;
	//check if double
	size_t pos = literal.find('.');
	if (pos != std::string::npos)
		return DOUBLE;
	//check if integer
	bool allDigits = true;
	for (std::size_t i = 0; i < literal.size(); i++) {
		char c = literal[i];
		if (i == 0 && (c == '+' || c == '-'))
			continue;
		if (!std::isdigit(static_cast<unsigned char>(c))) {
			allDigits = false;
			break;
		}
	}
	if (allDigits)
		return INT;
	return UNKNOWN;
}
