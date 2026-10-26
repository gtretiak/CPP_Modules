#include <iostream>
#include "RPN.hpp"
#include <string>
#define ARG "Error: Invalid number of arguments: <./RPN \"...\">"

int	main(int argc, char **argv) {
	if (argc != 2)
	{
		std::cerr << ARG << std::endl;
		return (1);
	}
	try {
		RPN	rpn;
		long res = rpn.evaluate(argv[1]);
		std::cout << res << std::endl;
	}
	catch (std::runtime_error &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}
