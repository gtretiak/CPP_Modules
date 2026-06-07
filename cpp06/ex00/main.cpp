#include "ScalarConverter.hpp"
#include <iostream>
#include <string>

int	main(int argc, char **argv) {
	if (argc != 2)
	{
		std::cerr << "Invalid number of arguments" << std::endl;
		return 1;
	}
	ScalarConverter::convert(argv[1]);
	return 0;
}
