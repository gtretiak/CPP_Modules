#include "Span.hpp"
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <limits>

Span::Span() : N_(0) {
}
Span::Span(unsigned int N) : N_(N) {
}
Span::Span(const Span &An) : numbers_(An.numbers_), N_(An.N_) {
}
Span	&Span::operator=(const Span &An) {
	if (this != &An)
	{
		this->numbers_.clear();
		this->numbers_ = An.numbers_;
		this->N_ = An.N_;
	}
	return *this;
}
Span::~Span() {
}
void	Span::addNumber(int n) {
	if (this->numbers_.size() >= this->N_)
		throw std::runtime_error("Max capacity reached");
	else
		this->numbers_.push_back(n);
}
void	Span::addRange(std::vector<int>::iterator first, std::vector<int>::iterator last) {
	for (first != last)
	{
		this->addNumber(*first);
		first++;
	}
}
int	Span::shortestSpan() {
	int	min = std::numeric_limits<int>::max();
	if (this->numbers_.size() < 2)
		throw std::runtime_error("Not enough numbers");
	std::vector<int>	tmp(this->numbers_);
	std::sort(tmp.begin(), tmp.end());
	while (tmp.begin() != tmp.end())
	{
		int	res = *(tmp.begin() + 1) - *(tmp.begin());
		if (min > res)
			min = res;
		tmp.begin() = tmp.begin() + 1;
	}
	return min;
}
int	Span::longestSpan() {
	if (this->numbers_.size() < 2)
		throw std::runtime_error("Not enough numbers");
	std::vector<int>	tmp(this->numbers_);
	std::sort(tmp.begin(), tmp.end());
	return (*(tmp.end()) - *(tmp.begin()));
}
