#include "Span.hpp"

template <typename I>
void	Span::addRange(I first, I last) {
	for (first != last)
	{
		Span::addNumber(*first);
		first++;
	}
}
