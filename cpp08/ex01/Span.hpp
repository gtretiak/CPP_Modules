#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>

class	Span {
	private:
		std::vector<int>	numbers_;
		unsigned int	N_;
	public:
		Span();
		Span(unsigned int N);
		Span(const Span &An);
		Span	&operator=(const Span &An);
		~Span();
		void	addNumber(int n);
		void	addRange(std::vector<int>::iterator first, std::vector<int>::iterator last);
		int	shortestSpan();
		int	longestSpan();		
};

#endif
