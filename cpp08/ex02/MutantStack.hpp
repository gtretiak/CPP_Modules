#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

template <typename T>
class MutantStack : public std::stack<T> {
	public:
		MutantStack();
		MutantStack(const MutantStack &An);
		MutantStack	&operator=(const MutantStack &An);
		~MutantStack();
		typedef typename std::stack<T>::container_type::iterator	iter; // iterator type of the underlying container
										      // by typedef we shorten the return type to just iter
		iter	begin();
		iter	end();
/*		protected:
 *			typedef typename Container	c;
 		T	&top();
		const T	&top();
		size_t	size() const;
		bool	empty() const;
		void	pop();
		void	push();*/
};

#include "MutantStack.tpp"

template <typename T>
MutantStack<T>::MutantStack() {}
template <typename T>
MutantStack<T>::MutantStack(const MutantStack &An) : std::stack<T>(An) {}
template <typename T>
MutantStack<T>	&MutantStack<T>::operator=(const MutantStack &An) {
	if (this != &An)
		std::stack<T>::operator=(An);
	return *this;
}
template <typename T>
MutantStack<T>::~MutantStack() {}

template <typename T>
typename MutantStack<T>::iter
MutantStack<T>::begin() {
	return this->c.begin();
}
template <typename T>
typename MutantStack<T>::iter
iter	MutantStack<T>::end() {
	return this->c.end();
}



#endif
