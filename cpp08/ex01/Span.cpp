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
int	Span::shortestSpan() const {
	int	min = std::numeric_limits<int>::max();
	if (this->numbers_.size() < 2)
		throw std::runtime_error("Not enough numbers");
	std::vector<int>	tmp(this->numbers_);
	std::sort(tmp.begin(), tmp.end());
	std::vector<int>::iterator	it = tmp.begin();
	while (it != tmp.end())
	{
		if (it + 1 == tmp.end())
			break ;
		int	res = *(it + 1) - *it;
		if (min > res)
			min = res;
		it++;
	}
	return min;
}
int	Span::longestSpan() const {
	if (this->numbers_.size() < 2)
		throw std::runtime_error("Not enough numbers");
/*	std::vector<int>	tmp(this->numbers_);
	std::sort(tmp.begin(), tmp.end());
	return (*(tmp.end() - 1) - *(tmp.begin()));*/
	return (*std::max_element(this->numbers_.begin(), this->numbers_.end()) - *std::min_element(this->numbers_.begin(), this->numbers_.end()));
}
