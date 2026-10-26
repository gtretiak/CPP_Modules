#include "PmergeMe.hpp"
#include <vector>
#include <deque>
#include <utility>
#include <algorithm> // std::lower_bound, for the binary search when inserting; std::swap, for swapping a pair; and std::distance
#define WRONG "Error: Sorting results do not match between std::vector and std::deque."

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
void	PmergeMe::sortV(std::vector<int> &seq) {
	int N = seq.size();
	if (N <= 1)
		return; // base case: already sorted
	int	straggler = -1; // default value, if even
	int NumPairs = N / 2;
	if (N % 2 != 0) {
		straggler = seq[N - 1]; // odd, so the last one is straggler
	}
	std::vector<pair<int,int> >	pairs = std::vector<pair<int,int> >();
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
	}
	sortV(winners); // recursively sort the winners
	

	// STEP 5: re-attach each sorted winner to a loser
  //   sortedPairs = empty PairSeq
  //   for each w in winners:
  //       find the FIRST pair in `pairs` whose .first == w
  //           (a pair already used has .first set to 0, so it never matches)
  //       sortedPairs.push_back( that pair )
  //       mark it used: that pair's .first = 0

  //   // STEP 6: main chain = b_1, then all winners in order
  //   chain = empty Seq
  //   chain.push_back( sortedPairs[0].second )              // b_1
  //   for each p in sortedPairs: chain.push_back( p.first ) // a_1 .. a_k

  //   // STEP 7: insert pending losers in Jacobsthal order
  //   P = k + (hasStraggler ? 1 : 0)
  //   insertPending(chain, sortedPairs, straggler, hasStraggler, k, P)

  //   // STEP 8: write back
  //   seq = chain

	// Why the “used” marker is 0: your inputs are always > 0, so 0 can never be a real winner. It saves you a flag array. Don’t use a vector<bool> for flags, because in the deque version that would sneak a vector into your deque implementation.

// Why this works with duplicates: if two pairs share the same winner value, it doesn’t matter which one is taken first. Both losers are ≤ that value, and both pairs will be consumed eventually.

// Insertion
// insertPending(chain, sortedPairs, straggler, hasStraggler, k, P):

//     prev = 1        // J(2) = 1: indices <= prev are already placed (b_1)
//     curr = 3        // J(3) = 3
//     // sequence: 1, 3, 5, 11, 21, 43 ...   next = curr + 2*prev

//     while prev < P:
//         high = min(curr, P)
//         low  = prev + 1

//         for i from high DOWN TO low:
//             // value to insert
//             if i <= k: value = sortedPairs[i-1].second      // b_i
//             else:      value = straggler                    // i == k+1

//             // search range end
//             if i <= k:
//                 limit = lowerBound(chain.begin, chain.end, sortedPairs[i-1].first)
//                 // iterator to a_i (or an equal value, see note)
//             else:
//                 limit = chain.end

//             pos = lowerBound(chain.begin, limit, value)
//             chain.insert(pos, value)

//         // advance the Jacobsthal sequence
//         newCurr = curr + 2*prev
//         prev = curr
//         curr = newCurr

// Check the group boundaries: for P = 12 the groups are 3,2, then 5,4, then 11,10,9,8,7,6, then 12 (clamped, since the next Jacobsthal number 21 exceeds P).

// Points to get right:

// Compute Jacobsthal with two scalars (prev, curr), not a container. A vector of Jacobsthal numbers in the deque version would again break implementation purity.
// Never reuse iterators across an insert. Compute limit and pos fresh in every iteration, because insertion invalidates iterators.
// Finding a_i by value. If the chain contains duplicates of a_i, lowerBound returns the first equal element, which may be earlier than the real a_i. This is still correct: everything before it is smaller than a_i, and b_i ≤ a_i, so the insert position can’t be later than that. The only effect is possibly a slightly smaller search range.
// Straggler = “no partner”. Its range is the whole chain. In the Jacobsthal order it comes first in its group, since its index is the highest.
// Use <-based lowerBound (std::lower_bound works for both containers). It returns the first position where the value can be inserted without breaking order.

// 4. Worked trace: 6 2 9 4 7 1 5
// Step	State
// n = 7, straggler = 5, k = 3	
// Pairs	(6,2), (9,4), (7,1)
// Winners	[6, 9, 7], recursive call returns [6, 7, 9]
// Rebuild	(6,2), (7,1), (9,4)
// Chain	[2, 6, 7, 9] (b_1, then winners)
// P = 4	pending: b_2 = 1 (a_2 = 7), b_3 = 4 (a_3 = 9), b_4 = 5 (straggler)

// Insertion order: group 1 is 3, 2, group 2 is 4.

// b_3 = 4, bound a_3 = 9 at position 3. Search [2, 6, 7], and 4 goes in at index 1, so the chain is [2, 4, 6, 7, 9].
// b_2 = 1, bound a_2 = 7 at position 3. Search [2, 4, 6], and 1 goes at index 0, so the chain is [1, 2, 4, 6, 7, 9].
// b_4 = 5 (straggler), whole chain. 5 goes before 6, giving [1, 2, 4, 5, 6, 7, 9] ✓.

// The recursive call fordJohnson([6, 9, 7]) itself goes through the same steps: pair (9,7), straggler 6, winners [9], chain [7, 9], P = 2, group 3 → clamped to 2: insert 6 into the whole chain, giving [6, 7, 9].

// 5. Edge cases to test by hand
// n	What happens
// 1	base case, returned immediately
// 2	one pair, winners of size 1, chain = [loser, winner], P = 1, no pending
// 3	one pair + straggler, P = 2, group 3 → clamp 2 → 2: only the straggler is inserted
// all equal	pairs are all (x,x); the rebuild with the 0 marker still consumes each pair once
// sorted / reversed	no special handling needed
// 3000 random with duplicates	shuf -r
// 6. Pitfalls checklist
// Marker bug: if you set .first = 0 before copying the pair into sortedPairs, you’d copy a corrupted pair. Copy first, mark afterwards.
// Off-by-one on indices: 1-based i maps to 0-based sortedPairs[i-1]. Write this mapping on paper before coding.
// Loop direction: the inner loop counts down. With size_t, a decreasing loop is only safe because low ≥ 2.
// Group termination: the while prev < P condition is what stops the loop. If P is 1 or 2, check it by hand.
// Recursion depth is about log₂(n), which is no concern for 3000 elements.
// Cost of the rebuild step is O(k²) at the top level (about a million operations for 3000 elements), acceptable here, and it is part of the timed work in both containers equally.
// 7. How to verify correctness (in a throwaway test program, not submitted)
// After sorting, check the sequence is non-decreasing.
// Compare against std::sort on the same input.
// Check that vector and deque results are identical.
// Loop it: thousands of random inputs of sizes 1 to 100, with small value ranges so duplicates are frequent.
// Optional, but great for the defense: count the comparisons in a test build. The theoretical worst case for n = 5, 11, 21 is 7, 26, 66 comparisons. If your count never exceeds those, your Jacobsthal order and bounds are right.

// the recursive core, the helpers, and a worked trace.
// compare numbers (winner - a, loser - b)
// recursion, binary
// recursively sorting winners
// build the chain b1, a1, a2...aN
// insert with binary search (std::lower_bound) the losers b2, b3...bN + straggler, comparing for every bN only up to aN (because aN is bigger anyway). 
// Jacobsthal sequence (each number is the previous one + twice the one before)
/*
    pairs.add( (max(seq[i],seq[i+1]), min(...)) )
    sort the pairs by winner, using fordJohnson recursively
    chain = [ loser of first pair ] + all winners
    pending = losers of pairs 2..n, then straggler (if any)
    for each index group in jacobsthalOrder(size of pending):
        for idx from group.high down to group.low:
            bound = position of partner winner of pending[idx] in chain
                    (end of chain for the straggler)
            pos = lowerBound(chain.begin, bound, pending[idx])
            chain.insert(pos, pending[idx])
    seq = chain*/

}
void	PmergeMe::sortD(std::deque<int> &seq) {
std::deque<pair<int, int> >	
int	straggler = -1; // if odd, the last element is left over

}
void	PmergeMe::compare() {
	if (this->_v.size() != this->_d.size()) {
		throw std::runtime_error << WRONG;
	}
	for (size_t i = 0; i < this->_v.size(); ++i) {
		if (this->_v[i] != this->_d[i]) {
			std::cerr << WRONG;
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