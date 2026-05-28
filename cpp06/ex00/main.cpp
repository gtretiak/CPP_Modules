#include "ScalarConverter.hpp"
#include <iostream>
#include <string>

int	main(int argc, char **argv) {
	if (argc != 2)
	{
		std::cerr << "Invalid number of arguments" << std::endl;
		return 1;
	}
	try {
		ScalarConverter::convert(argv[1]);
		return 0;
	}	
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
}
