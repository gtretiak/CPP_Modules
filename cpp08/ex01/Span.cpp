#include "Span.hpp"
#include <vector>
#include <algorithm>

template <typename Iter>
Span::Span() : N_(0) {
	this->numbers_ = NULL;
}
Span::Span(unsigned int N) N_(N) {
}
Span(const Span &An) : numbers_(An.numbers_), N_(An.N_) {
}
Span	&operator=(const Span &An) {
	if (this != &An)
	{
		delete this->numbers_;
		this->numbers_ = An.numbers_;
		this->N_ = An.N_;
	}
	return *this;
}
~Span() {
	delete this->numbers_;
}
void	addNumber(int n) {
}
void	addRange(Iter first, Iter last) {
}
int	shortestSpan() {
}
int	longestSpan() {
}
