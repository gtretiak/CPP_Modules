#ifndef ARRAY_HPP
#define ARRAY_HPP

template <typename T>
class	Array {
	private:
		unsigned int	size_;
		T	*numbers_;
	public:
		Array();
		Array(unsigned int n);
		unsigned int	size() const;
		Array(const Array &An);
		Array	&operator=(const Array &An);
		T	&operator[](unsigned int i);
		const T	&operator[](unsigned int i) const;
		~Array();
};

#include "Array.tpp"

#endif
