#include "Span.hpp"
#include <stdexcept>

template <typename I>
void	Span::addRange(I first, I last) {
	/*I	it = first;
	size_t	count = 0;
	while (it != last)
	{
		count++;		
		it++;
	}*/
	std::size_t	count = std::distance(first, last);
	if (this->numbers_.size() + count > this->N_)
		throw std::runtime_error("Impossible to insert the range - capacity is exceeded");
	while (first != last)
	{
		addNumber(*first);
		first++;
	}
}
