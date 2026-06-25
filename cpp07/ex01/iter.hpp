#ifndef ITER_HPP
#define ITER_HPP
#include <iostream>

template <typename T>
void	iter(T *addr, const size_t len, void (*f)(T &val)) {
	for (size_t i = 0; i < len; i++)
		f(addr[i]);
}

template <typename T>
void	iter(const T *addr, const size_t len, void (*f)(const T &val)) {
	for (size_t i = 0; i < len; i++)
		f(addr[i]);
}

template <typename T>
void	doubleValue(T &val) {
	std::cout << "This value was " << val;
	val *= 2;
	std::cout << " It's doubled. New value is " << val << std::endl;
}

template <typename T>
void	printValue(const T &val) {
	std::cout << "Just printing this value: " << val << std::endl;
}

#endif
