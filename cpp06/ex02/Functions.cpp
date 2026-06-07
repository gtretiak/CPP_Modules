#include "Functions.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Base	*generate(void) {
	int	randomN = std::rand() % 3;
	if (randomN == 0)
		return new A;
	else if (randomN == 1)
		return new B;
	else 
		return new C;
}
void	identify(Base *ptr) {
	std::cout << "Identification with pointer: ";
	if (dynamic_cast<A*>(ptr))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(ptr))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(ptr))
		std::cout << "C" << std::endl;
	else // should never happen
		std::cout << "Unknown class" << std::endl;
}
void	identify(Base &ref) {
	// Since reference can't be NULL, we need handle casting error
	std::cout << "Identification with reference: ";
	try {
		(void)dynamic_cast<A&>(ref);
		std::cout << "A" << std::endl;
		return ;
	}
	catch (std::exception &e) {
//		std::cerr << e.what() << std::endl; // preventing from mixing outputs
	}
	try {
		(void)dynamic_cast<B&>(ref);
		std::cout << "B" << std::endl;
		return ;
	}
	catch (std::exception &e) {
//		std::cerr << e.what() << std::endl; // same
	}
	try {
		(void)dynamic_cast<C&>(ref);
		std::cout << "C" << std::endl;
		return ;
	}
	catch (std::exception &e) {
//		std::cerr << e.what() << std::endl; // same
	}
}
