#ifndef EASYFIND_TPP
#define EASYFIND_TPP
#include <algorithm>
#include <stdexcept>

template <typename T>
typename T::iterator	easyfind(T &c, int ref) {
	typename T::iterator	it = std::find(c.begin(), c.end(), ref);
	if (it == c.end())
		throw std::runtime_error("not found");
	else
		return it;
}

template <typename T>
typename T::const_iterator	easyfind(const T &c, int ref) {
	typename T::const_iterator	it = std::find(c.begin(), c.end(), ref);
	if (it == c.end())
		throw std::runtime_error("not found");
	else
		return it;
}

#endif
