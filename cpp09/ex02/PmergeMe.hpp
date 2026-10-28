#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>

class	PmergeMe {
	private:
		std::vector<int>	_v;
		std::deque<int>		_d;
		void	sortV(std::vector<int> &seq);
		void	sortD(std::deque<int> &seq);
	public:
		PmergeMe();
		PmergeMe(const PmergeMe &An);
		PmergeMe	&operator=(const PmergeMe &An);
		~PmergeMe();
		void	fillV(int argc, char **argv);
		void	fillD(int argc, char **argv);
		void	sortV();
		void	sortD();
		void	compare();
		void	printSorted() const;
};

#endif
