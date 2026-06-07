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

static void	printInvalid() {
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: impossible" << std::endl;
	std::cout << "double: impossible" << std::endl;
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
		std::cout << std::fixed << std::setprecision(1) << static_cast<float>(num);
	else
		std::cout << static_cast<float>(num);
	std::cout << "f" << std::endl;
	if (num == static_cast<int>(num))
	{
		std::cout.unsetf(std::ios::floatfield);
		std::cout.precision(6);
	}
}
void	ScalarConverter::printDouble(double num) {
	std::cout << "double: ";
	if (num == static_cast<int>(num))
		std::cout << std::fixed << std::setprecision(1) << static_cast<double>(num) << std::endl;
	else
		std::cout << static_cast<double>(num) << std::endl;
	if (num == static_cast<int>(num))
	{
		std::cout.unsetf(std::ios::floatfield);
		std::cout.precision(6);
	}
}

double	ScalarConverter::parse(ScalarConverter::Type_ type, const std::string &var) {
	char	*end;
	if (type == CHAR)
	{
		if (var.length() == 1)
			return static_cast<double>(var[0]);
		else
			return static_cast<double>(var[1]);
	}
	return (std::strtod(var.c_str(), &end));
}

static bool	rejectNonDecimal(const std::string &var) {
	size_t	i = 0;
	if (var[i] == '+' || var[i] == '-')
		++i;
	if (i >= var.size() || !std::isdigit(var[i]))
		return true;
	if (var.find('x') != std::string::npos || var.find('X') != std::string::npos)
		return true;
	if (var[i] == '0' && i + 1 < var.size())
	{
		if (var[i + 1] != '.')
			return true; //042
	}
	return (false);
}

ScalarConverter::Type_	ScalarConverter::detectType(const std::string &var) {
	if (var == "-inf" || var == "+inf" || var == "inf" || var == "nan")
		return PSEUDO_D;
	else if (var == "inff" || var == "-inff" || var == "+inff" || var == "nanf")
		return PSEUDO_F;
	else if ((var.length() == 1 && !std::isdigit(var[0])) || (var.length() == 3 && var[0] == '\'' && var[2] == '\''))
		return CHAR;
	if (rejectNonDecimal(var))
		return INVALID;
	char	*end;
	double	num = std::strtod(var.c_str(), &end);
	if (*end == 'f' && std::isdigit(*(end - 1)) && *(end + 1) == '\0' && var.find('.') != std::string::npos)
		return FLOAT;
	else if (*end == '\0')
	{
		if (var.find('.') != std::string::npos)
			return DOUBLE;
		else if (num >= std::numeric_limits<int>::min() && num <= std::numeric_limits<int>::max())
			return INT;
		else
			return INVALID;
	}
	else
		return INVALID;
}

void	ScalarConverter::convert(const std::string &var) {
	ScalarConverter::Type_	type = detectType(var);
	if (type == INVALID)
	{
		printInvalid();
		return ;
	}
	double	val = parse(type, var);
	printChar(val);
	printInt(val);
	printFloat(val);
	printDouble(val);
}
ScalarConverter::~ScalarConverter() {}
