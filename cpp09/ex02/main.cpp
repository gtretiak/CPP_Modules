#include "PmergeMe.hpp"
#include <iostream>
#include <sys/time.h>
#define ARG "Error: Invalid number of arguments: <./PmergeMe Num1 Num2 ... NumN>"
#define INVALID "Error: Invalid argument(s) detected. Please provide only positive integers."

static void printTime(double elapsed1, double elapsed2, int N) {
		std::cout << "Time to process a range of " << N << " elements with std::vector: " << elapsed1 << " us" << std::endl;
		std::cout << "Time to process a range of " << N << " elements with std::deque: " << elapsed2 << " us" << std::endl;
}

static void printBefore(int argc, char **argv) {
	std::cout << "Before:";
	for (int i = 1; i < argc; i++) {
		std::cout << " " << argv[i];
		std::cout << std::endl;
	}
}

static bool isArgInvalid(int argc, char **argv) {	
	for (int i = 1; i < argc; i++) {
		std::string arg(argv[i]);
		if (arg.empty() || arg[0] == '-' || arg[0] == '0')
			return true;
		for (size_t j = 0; j < arg.size(); j++) {
			if (!std::isdigit(arg[j])) // reject non-digits
				return true;
			}
		}
		long num = std::stol(arg);
		if (num > std::numeric_limits<int>::max()) // reject int overflows
			return true;
	return false;
}

int	main(int argc, char **argv) {
	if (argc < 3) {
		std::cerr << ARG << std::endl;
		return (1);
	}
	if (isArgInvalid(argc, argv)) {
		std::cerr << INVALID << std::endl;
		return (1);
	}	
	printBefore(argc, argv);
	try {
		PmergeMe	sorter;
		struct timeval start, end;

		gettimeofday(&start, NULL);
		sorter.fillV(argc, argv);
		sorter.sortV(sorter.getV());
		gettimeofday(&end, NULL);
		double elapsed1 = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);		
		
		gettimeofday(&start, NULL);
		sorter.fillD(argc, argv);
		sorter.sortD(sorter.getD());
		gettimeofday(&end, NULL);
		double elapsed2 = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
		
		sorter.compare();
		sorter.printSorted();		
		printTime(elapsed1, elapsed2, argc - 1);
	}
	catch (std::runtime_error &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}
