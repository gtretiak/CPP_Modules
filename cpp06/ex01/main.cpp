#include "Serializer.hpp"
#include <string>
#include <iostream>
//#include <cstdint> // c++11style - forbidden
#include <stdint.h> // c-style
#include "Data.hpp"
#include <iomanip>

int	main(void) {
	Data	src = {42, '=', 42.0f, "Cool, huh?!"};
	uintptr_t	ptr = Serializer::serialize(&src);
	Data	*dest = Serializer::deserialize(ptr);
	if (&src == dest)
	{
		std::cout << "It's indeed the same memory address!" << std::endl;
		std::cout << "SRC -> int: " << src.i << " char: " << src.c << " float: " << std::fixed << std::setprecision(1) << src.f;
		std::cout.unsetf(std::ios::floatfield);
		std::cout.precision(6);
		std::cout << " string: " << src.str <<std::endl;
		std::cout << "DEST -> int: " << dest->i << " char: " << dest->c << " float: " << std::fixed << std::setprecision(1) << dest->f;
		std::cout.unsetf(std::ios::floatfield);
		std::cout.precision(6);
		std::cout << " string: " << dest->str <<std::endl;
}
	else
		std::cout << "Something is off" << std::endl;
	return 0;
}
