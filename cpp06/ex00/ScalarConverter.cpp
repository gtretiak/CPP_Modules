#include "ScalarConverter.hpp"
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <limits>
#include <iomanip> //io manipulators

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &An) {
	(void)An;
}
ScalarConverter	&ScalarConverter::operator=(const ScalarConverter &An) {
	(void)An;
	return (*this);
}

void	ScalarConverter::printChar(double num) {
	std::cout << "char: ";
	if (num != num || num < 0 || num > 127)
	{
		std::cout << "impossible" << std::endl;
		return ;
	}
	char	c = static_cast<char>(num);
	if (!std::isprint(c))
	{
		std::cout << "non displayable" << std::endl;
		return ;
	}
	std::cout << "'" << c << "'" << std::endl;
}
void	ScalarConverter::printInt(double num) {
	std::cout << "int: ";
	if (num != num || num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min())
	{
		std::cout << "impossible" << std::endl;
		return ;
	}
	std::cout << static_cast<int>(num) << std::endl;
}
void	ScalarConverter::printFloat(double num) {
	std::cout << "float: ";
	if (num == static_cast<int>(num))
		std::cout << static_cast<float>(num) << std::fixed << std::setprecision(1);
	else
		std::cout << static_cast<float>(num) << std::fixed;
	std::cout << ".f" << std::endl;
}
void	ScalarConverter::printDouble(double num) {
	std::cout << "double: ";
	if (num == static_cast<int>(num))
		std::cout << static_cast<double>(num) << std::fixed << std::setprecision(1) << std::endl;
	else
		std::cout << static_cast<double>(num) << std::fixed << std::endl;
}

double	ScalarConverter::parse(ScalarConverter::Type_ type, const std::string &var) {
	char	*end;
	if (type == INVALID)
		throw "Unexpected type";
	else if (type == CHAR)
	{
		if (var.length() == 1)
			return static_cast<double>(var[0]);
		else
			return static_cast<double>(var[1]);
	}
	return (std::strtod(var.c_str(), &end));
}

ScalarConverter::Type_	ScalarConverter::detectType(const std::string &var) {
	if (var == "-inf" || var == "+inf" || var == "inf" || var == "nan")
		return PSEUDO_D;
	else if (var == "inff" || var == "-inff" || var == "+inff" || var == "nanf")
		return PSEUDO_F;
	else if ((var.length() == 1 && std::isdigit(var[0])) || (var.length() == 3 && var[0] == '\'' && var[2] == '\''))
		return CHAR;
	char	*end;
	double	num = std::strtod(var.c_str(), &end);
	if (num >= std::numeric_limits<int>::min() && num <= std::numeric_limits<int>::max())
		return INT;
	else if (*end == 'f' && *(end + 1) == '\0')
		return FLOAT;
	else if (*end == '\0')
		return DOUBLE;
	else
		return INVALID;
}

void	ScalarConverter::convert(const std::string &var) {
	ScalarConverter::Type_	type = detectType(var);
	try {
		double	val = parse(type, var);
		printChar(val);
		printInt(val);
		printFloat(val);
		printDouble(val);
	}
	catch (std::exception &e) {
		throw "Unexpected type";
	}
}
ScalarConverter::~ScalarConverter() {}
