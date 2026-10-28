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
	// Each pair becomes (a_i, b_i): a_i is the larger value and b_i the smaller.
	// The odd leftover, if present, has no partner and is inserted last as the straggler.
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
		// Put the larger member first; this gives a_i >= b_i for every pair.
		if (x >= y)
			pairs.push_back(std::make_pair(x, y));
		else
			pairs.push_back(std::make_pair(y, x));
	}
	std::vector<int>	winners = std::vector<int>();
	for (size_t i = 0; i < pairs.size(); ++i) {
		winners.push_back(pairs[i].first);
	} // Winners	[6, 9, 7], then 9

	// Recursively sort only the a_i values. Their partners remain attached in pairs.
	sortV(winners); // recursively sort the winners, after the next iteration it would be [6, 7, 9]
	
	std::vector<std::pair<int,int> >	sortedPairs = std::vector<std::pair<int,int> >();
	// Restore each winner's original loser, now ordered by the sorted winners.
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
	// b_1 is seeded first; then add every sorted winner a_i. This is the initial chain.
	chain.push_back(sortedPairs[0].second); // b_1 = 2
	for (size_t i = 0; i < sortedPairs.size(); ++i) {
		chain.push_back(sortedPairs[i].first); // a_1 .. a_k (all winners) = 6, 7, 9
	}
	// chain = 2, 6, 7, 9
	// Pending indices are 1-based: b_1 is already seeded, followed by b_2...b_k;
	// if there is a straggler it occupies index k+1. P is the final index for this call.
	int P = NumPairs + (straggler != -1 ? 1 : 0);
	insertPendingV(chain, sortedPairs, straggler, NumPairs, P);
	// initially chain = 2, 6, 7, 9, then after inserting b_3 = 4 (bound a_3 = 9) chain = 2, 4, 6, 7, 9, then after inserting b_2 = 1 (bound a_2 = 7) chain = 1, 2, 4, 6, 7, 9, then after inserting b_4 = 5 (straggler) chain = 1, 2, 4, 5, 6, 7, 9
	// sortedPairs initially (6,2), (7,1), (9,4), then after inserting b_3 = 4 (bound a_3 = 9) sortedPairs = (6,2), (7,1), (9,4), then after inserting b_2 = 1 (bound a_2 = 7) sortedPairs = (6,2), (7,1), (9,4), then after inserting b_4 = 5 (straggler) sortedPairs = (6,2), (7,1), (9,4)
	// straggler always remains the same = 5
	// NumPairs always remains the same = 3
	// For the example, recursive calls have P=4 at size 7, P=2 at size 3,
	// and P=1 at size 2. Size 1 returns at the base case before calculating P.
	seq = chain; // writing back the sorted sequence
}

static void	insertPendingV(std::vector<int> &chain, const std::vector<std::pair<int,int> > &sortedPairs, int straggler, int NumPairs, int P) {
	// ---------------------------------------------------------------
	// What this function does:
	//   1) build the initial chain with b_1 and all winners a_1..a_k
	//   2) insert remaining losers b_2..b_k and the straggler in a special
	//      Jacobsthal order, using binary search to place each value before
	//      the relevant winner bound
	//
	// Example with sequence: [6, 2, 9, 4, 7, 1, 5]
	//   pairs = [(9, 6?), no, after ordering each pair: (6,2), (9,4), (7,1)]
	//   winners = [6, 9, 7]
	//   sorted winners = [6, 7, 9]
	//   sortedPairs after reordering by winner becomes:
	//       [(6,2), (7,1), (9,4)]
	//
	//   initial chain = [2, 6, 7, 9]
	//
	//   pending values are:
	//       b_2 = 1  (bound a_2 = 7)
	//       b_3 = 4  (bound a_3 = 9)
	//       straggler = 5 (no bound; insert in whole chain)
	//
	//   The algorithm does NOT insert in natural order b_2, b_3, straggler.
	//   It follows Jacobsthal groups: 3,2, then 4.
	//
	//   First group: index 3 then 2
	//     - i = 3 => value = b_3 = 4, bound = a_3 = 9
	//       search before 9, insert 4 -> [2, 4, 6, 7, 9]
	//     - i = 2 => value = b_2 = 1, bound = a_2 = 7
	//       search before 7, insert 1 -> [1, 2, 4, 6, 7, 9]
	//
	//   Second group: index 4 (straggler)
	//     - i = 4 => value = 5, bound = end of chain
	//       search whole chain, insert 5 -> [1, 2, 4, 5, 6, 7, 9]
	//
	// Why this order matters:
	//   The Jacobsthal groups guarantee that every inserted element is placed
	//   using a valid bound, and that the smallest inserts are delayed until the
	//   structure is large enough. This keeps the tree/chain structure balanced
	//   enough for efficient binary insertion while preserving correctness.
	// ---------------------------------------------------------------

	// Jacobsthal boundaries: 1, 3, 5, 11, ...
	// prev and curr are the previous and current Jacobsthal boundary values.
	// Example for P = 4: groups are [3, 2] then [4].
	// The loop keeps inserting in descending index order inside each group.
	int prev = 1; // J(2) = 1: b_1 already placed, so we start after it
	int curr = 3; // J(3) = 3
	while (prev < P) {
		int high = std::min(curr, P);
		int low = prev + 1;
		for (int i = high; i >= low; --i) {
			int value;
			if (i <= NumPairs) {
				// Pending index i corresponds to pair i in 1-based indexing.
				// Example: i = 3 => value = sortedPairs[2].second = b_3
				value = sortedPairs[i - 1].second;
			} else {
				// If there is an odd leftover, it is inserted as the last pending value.
				value = straggler;
			}

			std::vector<int>::iterator limit;
			if (i <= NumPairs) {
				// We must insert b_i before a_i. The winner a_i is the upper bound.
				// So the binary search only runs in the range before a_i.
				limit = std::lower_bound(chain.begin(), chain.end(), sortedPairs[i - 1].first);
			} else {
				// Straggler has no winner partner, so it can be inserted anywhere in the chain.
				limit = chain.end();
			}

			// Insert value in sorted order with respect to the allowed bound.
			std::vector<int>::iterator pos = std::lower_bound(chain.begin(), limit, value);
			chain.insert(pos, value);
		}
		int newCurr = curr + 2 * prev;
		prev = curr;
		curr = newCurr;
	}

	// Detailed logic:
	//
	// 1) We do NOT insert the losers in the natural order b_2, b_3, ...
	//    Instead, we use Jacobsthal order: 3, 2, 5, 4, 11, 10, 9, 8, 7, 6, ...
	//
	// 2) Each loser b_i is inserted before its paired winner a_i.
	//    That means for b_i we search only up to the first occurrence of a_i.
	//    This keeps the insertion efficient.
	//
	// 3) If the input had an odd number of elements, the last element is a
	//    straggler with no partner. In that case, the bound is the end of the
	//    chain, and we insert it using the same lower_bound strategy.
	//
	// 4) Why lower_bound is correct:
	//    - If the value is smaller than the bound, it must go before that bound.
	//    - If the value is greater/equal than the bound, it must go after it.
	//    - Because b_i <= a_i, all valid insertion positions for b_i lie before a_i.
	//
	// 5) The comment block above with [6,2,9,4,7,1,5] is the same logic as this
	//    implementation. The chain is reconstructed as:
	//       [2, 6, 7, 9]
	//    then the pending values are inserted in Jacobsthal order:
	//       4, 1, 5
	//    resulting in:
	//       [1, 2, 4, 5, 6, 7, 9]
	//
	// 6) limit and pos must be computed after the previous insertion,
	//    because inserting into the vector invalidates iterators.
	//
	// 7) The reason this is efficient is that each item is inserted with a
	//    binary search over a smaller and smaller valid range, instead of doing a
	//    full linear scan over the whole chain.
	// ------------------------------------------------------------------
}
void	PmergeMe::sortD(std::deque<int> &seq) {
	int N = seq.size();
	if (N <= 1)
		return;
	// This is the same pair / recurse / chain / pending-insert process as sortV,
	// implemented separately so the algorithm operates directly on std::deque.
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
	// Use the same Jacobsthal group order as the vector implementation.
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
			// Binary-insert b_i before its partner, or insert the unpaired value anywhere.
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