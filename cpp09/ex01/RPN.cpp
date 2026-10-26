#include "RPN.hpp"
#include <list>
#include <stack>
#include <sstream>
#include <cctype>
#include <limits>
#include <stdexcept>
#define EMPTY "Expression empty"
#define INVALID "Unexpected token in expression"
#define MALFORMED "Expression malformed"
#define ZERO "Division by 0 detected"
#define OVERFLOW "Overflow detected"

RPN::RPN () {
	_stack = std::stack<long, std::list<long> >();
}
RPN::RPN(const RPN &An) : _stack(An._stack) {}
RPN	&RPN::operator=(const RPN &An) {
	if (this != &An)
	{
		this->_stack = An._stack;
	}
	return (*this);
}
RPN::~RPN() {}

long	RPN::evaluate(const std::string &arg) {
	if (arg.empty())
		throw std::runtime_error(EMPTY);
	std::string	token;
	std::istringstream	stream(arg);
	while (stream >> token) {
		if (token.size() != 1)
			throw std::runtime_error(INVALID);
		unsigned char c = static_cast<unsigned char>(token[0]); 
		if (std::isdigit(c))
			this->_stack.push(c - '0');
		else {
			if (this->_stack.size() < 2)
				throw std::runtime_error(MALFORMED);
			long b = this->_stack.top();
			this->_stack.pop();
			long a = this->_stack.top();
			this->_stack.pop();
			switch (c)
			{
			case '+':
				if ((b > 0 && a > std::numeric_limits<int>::max() - b) || (b < 0 && a < std::numeric_limits<int>::min() - b))
					throw std::runtime_error(OVERFLOW);
				_stack.push(a + b);
				break;
			case '-':
				if ((b < 0 && a > std::numeric_limits<int>::max() + b) || (b > 0 && a < std::numeric_limits<int>::min() + b))
					throw std::runtime_error(OVERFLOW);
				_stack.push(a - b); 
				break;
			case '*':
				if ((a > 0 && b > 0 && a > std::numeric_limits<int>::max() / b) || (a > 0 && b < 0 && b < std::numeric_limits<int>::min() / a)
			|| (a < 0 && b > 0 && a < std::numeric_limits<int>::min() / b) || (a < 0 && b < 0 && a < std::numeric_limits<int>::max() / b))
					throw std::runtime_error(OVERFLOW);
				_stack.push(a * b);
				break;
			case '/':
				if (b == 0)
					throw std::runtime_error(ZERO);
				else if (a == std::numeric_limits<int>::min() && b == -1)
					throw std::runtime_error(OVERFLOW);
				_stack.push(a / b);
				break;
			default:
				throw std::runtime_error(INVALID);
			}
		}
	}
	if (this->_stack.size() != 1)
		throw std::runtime_error(MALFORMED);
	return this->_stack.top();
}