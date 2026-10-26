#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <vector>
#include <deque>
#include <algorithm> // std::lower_bound, for the binary search when inserting; std::swap, for swapping a pair; and std::distance

class	PmergeMe {
	private:
		std::vector<int>	v;
		std::deque<int>		d;
	public:
		PmergeMe();
		PmergeMe(const PmergeMe &An);
		PmergeMe	&operator=(const PmergeMe &An);
		~PmergeMe();
		sortV();
		sortD();
};
// reject non-digits, negative values and 0, int overflows, doubles (with '.'), 
// pairs, recursion, binary
// pair up elements (if odd - the last one is left over)
// compare numbers (winner - a, loser - b)
// recursively sorting winners
// build the chain b1, a1, a2...aN
// insert with binary search (std::lower_bound) the losers b2, b3...bN + straggler, comparing for every bN only up to aN (because aN is bigger anyway). 
// Jacobsthal sequence (each number is the previous one + twice the one before)

#endif
