#include "myTemplates.hpp"
#include <iostream>

int	main(void) {
	int	a = 2;
	int	b = 3;
	::swap(a, b);
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
	std::cout << "max(a, b) = " << ::max(a, b) << std::endl;
	std::string str1 = "hello";
	std::string str2 = "world";
	::swap(str1, str2);
	std::cout << "str1 = " << str1 << ", str2 = " << str2 << std::endl;
	std::cout << "min(str1, str2) = " << ::min(str1, str2) << std::endl;
	std::cout << "max(str1, str2) = " << ::max(str1, str2) << std::endl;
	return 0;
}
