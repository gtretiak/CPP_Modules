#ifndef ITER_HPP
#define ITER_HPP

template <typename T, template F>
void	iter(T *addr, const size_t len, F f) {
	for (size_t i = 0; i < len; i++)
		f(addr[i]);
}

#endif
