#include "PmergeMe.hpp"
#include <iostream>
#include <ctime>
#include <sys/time.h>
#define ARG "Error: Invalid number of arguments: <./PmergeMe Num1 Num2 ... NumN>"

int	main(int argc, char **argv) {
	if (argc < 3)
		std::cerr << ARG << std::endl;
	try {
		// printing before
		//
		// timer on: clock(), gettimeofday()
		// filling a container, preparation
		// PmergeMe.sortV(?) TODO
		// timer off (storing the result)
		// 
		// timer on
		// filling a container, preparation
		// PmergeMe.sortD(?) TODO
		// timer off (storing the result)
		// 
		// printing after
		// printing results
			}
	catch (std::runtime_error e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}
