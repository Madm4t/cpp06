#include "ScalarConverter.hpp"
#include <cctype>
#include <iostream>
#include <limits>
#include <cmath> //std::isnan(); std::isinf()
#include <iomanip> //std::fixed(); std::setprecision()
//stoi() convert string to int (used since c++11), atoi() is (C-Style)
//stof() or atof() convert string to float
//stod() convert string to double

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
	for (std::size_t i = 0; i < literal.size(); i++) {
		char c = literal[i];
		if (i == 0 && (c == '+' || c == '-'))
			continue;
		if (!std::isdigit(static_cast<unsigned char>(c))) {
			return UNKNOWN;
		}
	}
	return INT;
}

size_t calculatePrecision(const std::string& literal) {
	size_t pos_dot = literal.find('.');
	if (pos_dot == std::string::npos)
		return 1;
	size_t str_len = (literal.back() == 'f') ? literal.size() - 1 : literal.size();
	return (str_len - pos_dot - 1);
}

static void printImpossible() {
	std::cout
		<< "char:	impossible\n"
		<< "int:	impossible\n"
		<< "float:	impossible\n"
		<< "double:	impossible\n";
}

static void printResult(char c, int i, float f, double d, std::size_t prec) {
	//char
	if (d < std::numeric_limits<char>::min() 
		|| d > std::numeric_limits<char>::max())
		std::cout << "char: impossible\n";
	else if (std::isprint(static_cast<unsigned char>(c)))
		std::cout << "char: '" << c << "'\n";
	else
		std::cout << "char: Non displayable\n";

	//int
	if (std::isnan(d) || std::isinf(d) || d < std::numeric_limits<int>::min() 
		|| d > std::numeric_limits<int>::max())
	{
		std::cout << "int: impossible\n";
	}
	else {
		std::cout << "int: " << i << "\n";
	}

	//float & double
	std::cout << std::fixed << std::setprecision(prec) //sets std to fixed-point notation and sets precision
		<< "float: " << f << "f\n"
		<< "double: " << d << "\n";
}

void ScalarConverter::convert(const std::string& literal)
{
	literalType type = detectType(literal);

	if (type == PSEUDO_FLOAT) {
		std::string dvalue = literal.substr(0, literal.size() - 1);
		std::cout
			<< "char: impossible\n"
			<< "int: impossible\n"
			<< "float: " << literal << "\n"
			<< "double: " << dvalue << "\n";
		return;
	}
	if (type == PSEUDO_DOUBLE) {
		std::string fvalue = literal + 'f';
		std::cout
			<< "char: impossible\n"
			<< "int: impossible\n"
			<< "float: " << fvalue << "\n"
			<< "double: " << literal << "\n";
		return;
	}
	if (type == UNKNOWN) {
		printImpossible();
		return;
	}

	char c = 0;
	int i = 0;
	float f = 0.0f;
	double d = 0.0;

	try {
		switch (type) {
			case CHAR:
				c = literal[0];
				i = static_cast<int>(c);
				f = static_cast<float>(c);
				d = static_cast<double>(c);
				break;
			case INT:
				i = std::stoi(literal);
				c = static_cast<char>(i);
				f = static_cast<float>(i);
				d = static_cast<double>(i);
				break;
			case FLOAT:
				f = std::stof(literal);
				c = static_cast<char>(f);
				i = static_cast<int>(f);
				d = static_cast<double>(f);
				break;
			case DOUBLE:
				d = std::stod(literal);
				c = static_cast<char>(d);
				i = static_cast<int>(d);
				f = static_cast<float>(d);
				break;
			default:
				break;
		}
	}
	catch(...) {
		printImpossible();
		return;
	}
	printResult(c, i, f, d, calculatePrecision(literal));
}

