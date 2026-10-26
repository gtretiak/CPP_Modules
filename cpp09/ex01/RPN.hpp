#ifndef RPN_HPP
#define RPN_HPP
#include <list>
#include <stack>
#include <string>

class	RPN {
	private:
		std::stack<long, std::list<long> >	_stack;
	public:
		RPN();
		RPN(const RPN &An);
		RPN	&operator=(const RPN &An);
		~RPN();
		long	evaluate(const std::string &arg);
};

#endif