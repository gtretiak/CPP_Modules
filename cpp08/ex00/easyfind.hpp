#ifndef EASYFIND_HPP
#define EASYFIND_HPP

template <typename T>
typename T::iterator	easyfind(T &c, int ref);
template <typename T>
typename T::const_iterator	easyfind(const T &c, int ref);

#include "easyfind.tpp"

#endif
