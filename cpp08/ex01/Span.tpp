#include "Span.hpp"

template <typename I>
void	Span<I>::addRange(I first, I last) {
	while (first != last)
	{
		Span<I>::addNumber(*first);
		first++;
	}
}
