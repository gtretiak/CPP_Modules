#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP
#include <stack>
#include <deque>
template <typename T>
class MutantStack : public std::stack<T> {
	// internally std::stack is a container adapter with 'c' protected attribute (by default std::deque)
	//	protected:
	//		typedef typename Container	c;
	public:
		MutantStack();
		MutantStack(const MutantStack<T> &An);
		MutantStack<T>	&operator=(const MutantStack<T> &An);
		virtual ~MutantStack();
		typedef typename std::stack<T>::container_type::iterator	iterator;
		typedef typename std::stack<T>::container_type::const_iterator	const_iterator;
		typedef typename std::stack<T>::container_type::reverse_iterator	reverse_iterator;
		typedef typename std::stack<T>::container_type::const_reverse_iterator	const_reverse_iterator;
		// iterator type of the underlying container,		// by typedef we shorten the return type to just iter
		iterator	begin();
		iterator	end();
		const_iterator	begin() const;
		const_iterator	end() const;
		reverse_iterator	rbegin();
		reverse_iterator	rend();
		const_reverse_iterator	rbegin() const;
		const_reverse_iterator	rend() const;
};
#include "MutantStack.tpp"
#endif
