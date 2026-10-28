#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>

class	PmergeMe {
	private:
		std::vector<int>	_v;
		std::deque<int>		_d;
		// private helpers: recursion + insertion per container?
	public:
		PmergeMe();
		PmergeMe(const PmergeMe &An);
		PmergeMe	&operator=(const PmergeMe &An);
		~PmergeMe();
		void	fillV(int argc, char **argv);
		void	fillD(int argc, char **argv);
		void	sortV();
		void	sortD();
		void	sortV(std::vector<int> &seq);
		void	sortD(std::deque<int> &seq);
		std::vector<int>	getV() const;
		std::deque<int>	getD() const;
		void	compare();
		void	printSorted() const;
};

#endif
