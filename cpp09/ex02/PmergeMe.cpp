#include "PmergeMe.hpp"
#include <vector>
#include <deque>
#include <utility>
#include <iostream>
#include <algorithm> // std::lower_bound, for the binary search when inserting
#include <stdexcept>
#define WRONG "Sorting results do not match between std::vector and std::deque."

static void insertPendingV(std::vector<int> &chain, const std::vector<std::pair<int, int> > &sortedPairs, int straggler, int NumPairs, int P);
static void insertPendingD(std::deque<int> &chain, const std::deque<std::pair<int, int> > &sortedPairs, int straggler, int NumPairs, int P);

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &An) : _v(An._v), _d(An._d) {}
PmergeMe	&PmergeMe::operator=(const PmergeMe &An) {
	if (this != &An)
	{
		this->_v = An._v;
		this->_d = An._d;
	}
	return (*this);
}
PmergeMe::~PmergeMe() {}

void	PmergeMe::fillV(int argc, char **argv) {
	this->_v.clear();
	for (int i = 1; i < argc; i++) {
		long num = std::strtol(argv[i], NULL, 10);
		this->_v.push_back(static_cast<int>(num));
	}
}
void	PmergeMe::fillD(int argc, char **argv) {
	this->_d.clear();
	for (int i = 1; i < argc; i++) {
		long num = std::strtol(argv[i], NULL, 10);
		this->_d.push_back(static_cast<int>(num));
	}
}
void	PmergeMe::sortV() {
	sortV(this->_v);
}
void	PmergeMe::sortD() {
	sortD(this->_d);
}
void	PmergeMe::sortV(std::vector<int> &seq) { // say, we start with 6 2 9 4 7 1 5, then 6 9 7, then 9
	int N = seq.size(); // 7, then 3, then 1
	if (N <= 1)
		return; // base case: already sorted
	int	straggler = -1; // default value, if even 
	int NumPairs = N / 2; // 3, then 1
	if (N % 2 != 0) {
		straggler = seq[N - 1]; // odd, so the last one is straggler, // initially 5, then 7
	}
	
	// Pairs	(6,2), (9,4), (7,1), then (6,9)
	std::vector<std::pair<int,int> >	pairs = std::vector<std::pair<int,int> >();
	for (int i = 0; i < NumPairs; ++i) {
		int x = seq[2 * i];
		int y = seq[2 * i + 1];
		if (x >= y)
			pairs.push_back(std::make_pair(x, y));
		else
			pairs.push_back(std::make_pair(y, x));
	}
	std::vector<int>	winners = std::vector<int>();
	for (size_t i = 0; i < pairs.size(); ++i) {
		winners.push_back(pairs[i].first);
	} // Winners	[6, 9, 7], then 9

	sortV(winners); // recursively sort the winners, after the next iteration it would be [6, 7, 9]
	
	std::vector<std::pair<int,int> >	sortedPairs = std::vector<std::pair<int,int> >();
	for (size_t i = 0; i < winners.size(); ++i) {
		for (size_t j = 0; j < pairs.size(); ++j) {
			if (pairs[j].first == winners[i]) {
				sortedPairs.push_back(pairs[j]); // sortedPairs	(6,2), (7,1), (9,4)
				pairs[j].first = 0; // mark as used (because all inputs are positive, 0 is a safe marker)
				break;
			}
		}
	}
	std::vector<int>	chain = std::vector<int>();
	chain.push_back(sortedPairs[0].second); // b_1 = 2
	for (size_t i = 0; i < sortedPairs.size(); ++i) {
		chain.push_back(sortedPairs[i].first); // a_1 .. a_k (all winners) = 6, 7, 9
	}
	// chain = 2, 6, 7, 9
	int P = NumPairs + (straggler != -1 ? 1 : 0); // number of the // highest 1-based pending index in the pending list (losers + straggler) = 4 (b_1 is already in the chain), then 2, then 1, then 0
	insertPendingV(chain, sortedPairs, straggler, NumPairs, P);
	// initially chain = 2, 6, 7, 9, then after inserting b_3 = 4 (bound a_3 = 9) chain = 2, 4, 6, 7, 9, then after inserting b_2 = 1 (bound a_2 = 7) chain = 1, 2, 4, 6, 7, 9, then after inserting b_4 = 5 (straggler) chain = 1, 2, 4, 5, 6, 7, 9
	// sortedPairs initially (6,2), (7,1), (9,4), then after inserting b_3 = 4 (bound a_3 = 9) sortedPairs = (6,2), (7,1), (9,4), then after inserting b_2 = 1 (bound a_2 = 7) sortedPairs = (6,2), (7,1), (9,4), then after inserting b_4 = 5 (straggler) sortedPairs = (6,2), (7,1), (9,4)
	// straggler always remains the same = 5
	// NumPairs always remains the same = 3
	// P = 4, then 2, then 1, then 0
	seq = chain; // writing back the sorted sequence
}

static void	insertPendingV(std::vector<int> &chain, const std::vector<std::pair<int,int> > &sortedPairs, int straggler, int NumPairs, int P) {
	int prev = 1; // J(2) = 1: indices <= prev are already placed (b_1)
	int curr = 3; // J(3) = 3
	while (prev < P) {
		int high = std::min(curr, P);
		int low = prev + 1;
		for (int i = high; i >= low; --i) {
			int value;
			if (i <= NumPairs) {
				value = sortedPairs[i - 1].second; // b_i
			} else {
				value = straggler; // i == k+1
			}
			std::vector<int>::iterator limit;
			if (i <= NumPairs) {
				limit = std::lower_bound(chain.begin(), chain.end(), sortedPairs[i - 1].first); // a_i
			} else {
				limit = chain.end();
			}
			std::vector<int>::iterator pos = std::lower_bound(chain.begin(), limit, value);
			chain.insert(pos, value);
		}
		int newCurr = curr + 2 * prev;
		prev = curr;
		curr = newCurr;
	}

// Check the group boundaries: for P = 12 the groups are 3,2, then 5,4, then 11,10,9,8,7,6, then 12 (clamped, since the next Jacobsthal number 21 exceeds P).

// Points to get right:
// Never reuse iterators across an insert. Compute limit and pos fresh in every iteration, because insertion invalidates iterators.
// Finding a_i by value. If the chain contains duplicates of a_i, lowerBound returns the first equal element, which may be earlier than the real a_i. This is still correct: everything before it is smaller than a_i, and b_i ≤ a_i, so the insert position can’t be later than that. The only effect is possibly a slightly smaller search range.
// Straggler = “no partner”. Its range is the whole chain. In the Jacobsthal order it comes first in its group, since its index is the highest.
// Use <-based lowerBound (std::lower_bound works for both containers). It returns the first position where the value can be inserted without breaking order.

// P = 4	pending: b_2 = 1 (a_2 = 7), b_3 = 4 (a_3 = 9), b_4 = 5 (straggler)

// Insertion order: group 1 is 3, 2, group 2 is 4.

// b_3 = 4, bound a_3 = 9 at position 3. Search [2, 6, 7], and 4 goes in at index 1, so the chain is [2, 4, 6, 7, 9].
// b_2 = 1, bound a_2 = 7 at position 3. Search [2, 4, 6], and 1 goes at index 0, so the chain is [1, 2, 4, 6, 7, 9].
// b_4 = 5 (straggler), whole chain. 5 goes before 6, giving [1, 2, 4, 5, 6, 7, 9] ✓.

// The recursive call fordJohnson([6, 9, 7]) itself goes through the same steps: pair (9,7), straggler 6, winners [9], chain [7, 9], P = 2, group 3 → clamped to 2: insert 6 into the whole chain, giving [6, 7, 9].

// 5. Edge cases to test by hand
// 2	one pair, winners of size 1, chain = [loser, winner], P = 1, no pending
// 3	one pair + straggler, P = 2, group 3 → clamp 2 → 2: only the straggler is inserted
// all equal	pairs are all (x,x); the rebuild with the 0 marker still consumes each pair once
// sorted / reversed	no special handling needed
// 3000 random with duplicates	shuf -r

// 6. Pitfalls checklist
// Off-by-one on indices: 1-based i maps to 0-based sortedPairs[i-1]. Write this mapping on paper before coding.
// Loop direction: the inner loop counts down. With size_t, a decreasing loop is only safe because low ≥ 2.
// Group termination: the while prev < P condition is what stops the loop. If P is 1 or 2, check it by hand.
// Recursion depth is about log₂(n), which is no concern for 3000 elements.
// Cost of the rebuild step is O(k²) at the top level (about a million operations for 3000 elements), acceptable here, and it is part of the timed work in both containers equally.

// 7. How to verify correctness (in a throwaway test program, not submitted)
// Optional, but great for the defense: count the comparisons in a test build. The theoretical worst case for n = 5, 11, 21 is 7, 26, 66 comparisons. If your count never exceeds those, your Jacobsthal order and bounds are right.

// binary
// insert with binary search (std::lower_bound) the losers b2, b3...bN + straggler, comparing for every bN only up to aN (because aN is bigger anyway). 
// Jacobsthal sequence (each number is the previous one + twice the one before)
/*
    pending = losers of pairs 2..n, then straggler (if any)
    for each index group in jacobsthalOrder(size of pending):
        for idx from group.high down to group.low:
            bound = position of partner winner of pending[idx] in chain
                    (end of chain for the straggler)
            pos = lowerBound(chain.begin, bound, pending[idx])
            chain.insert(pos, pending[idx])
    */

}
void	PmergeMe::sortD(std::deque<int> &seq) {
	int N = seq.size();
	if (N <= 1)
		return;
	int	straggler = -1;
	int NumPairs = N / 2;
	if (N % 2 != 0) {
		straggler = seq[N - 1];
	}
	std::deque<std::pair<int,int> >	pairs = std::deque<std::pair<int,int> >();
	for (int i = 0; i < NumPairs; ++i) {
		int x = seq[2 * i];
		int y = seq[2 * i + 1];
		if (x >= y)
			pairs.push_back(std::make_pair(x, y));
		else
			pairs.push_back(std::make_pair(y, x));
	}
	std::deque<int>	winners = std::deque<int>();
	for (size_t i = 0; i < pairs.size(); ++i) {
		winners.push_back(pairs[i].first);
	}
	sortD(winners);
	std::deque<std::pair<int,int> >	sortedPairs = std::deque<std::pair<int,int> >();
	for (size_t i = 0; i < winners.size(); ++i) {
		for (size_t j = 0; j < pairs.size(); ++j) {
			if (pairs[j].first == winners[i]) {
				sortedPairs.push_back(pairs[j]);
				pairs[j].first = 0;
				break;
			}
		}
	}
	std::deque<int>	chain = std::deque<int>();
	chain.push_back(sortedPairs[0].second);
	for (size_t i = 0; i < sortedPairs.size(); ++i) {
		chain.push_back(sortedPairs[i].first);
	}
	int P = NumPairs + (straggler != -1 ? 1 : 0);
	insertPendingD(chain, sortedPairs, straggler, NumPairs, P);
	seq = chain;
} 

static void	insertPendingD(std::deque<int> &chain, const std::deque<std::pair<int,int> > &sortedPairs, int straggler, int NumPairs, int P) {
	int prev = 1;
	int curr = 3;
	while (prev < P) {
		int high = std::min(curr, P);
		int low = prev + 1;
		for (int i = high; i >= low; --i) {
			int value;
			if (i <= NumPairs) {
				value = sortedPairs[i - 1].second; // b_i
			} else {
				value = straggler;
			}
			std::deque<int>::iterator limit;
			if (i <= NumPairs) {
				limit = std::lower_bound(chain.begin(), chain.end(), sortedPairs[i - 1].first); // a_i
			} else {
				limit = chain.end();
			}
			std::deque<int>::iterator pos = std::lower_bound(chain.begin(), limit, value);
			chain.insert(pos, value);
		}
		int newCurr = curr + 2 * prev;
		prev = curr;
		curr = newCurr;
	}
}
void	PmergeMe::compare() {
	if (this->_v.size() != this->_d.size()) {
		throw std::runtime_error(WRONG);
	}
	for (size_t i = 0; i < this->_v.size(); ++i) {
		if (this->_v[i] != this->_d[i]) {
			throw std::runtime_error(WRONG);
		}
	}
}
void	PmergeMe::printSorted() const {
	std::cout << "After: ";
	for (size_t i = 0; i < this->_v.size(); ++i) {
		std::cout << this->_v[i] << " ";
	}
	std::cout << std::endl;
}