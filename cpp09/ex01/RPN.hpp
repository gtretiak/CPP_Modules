#ifndef RPN_HPP
#define RPN_HPP
#include <list>
#include <stack>
#include <algorithm>

class	RPN {
	RPN() = 0;
	RPN(const RPN &An);
	RPN	*operator=(const RPN &An);
	~RPN();
	int	evaluate(const std::string &arg);
};
// empty argument (throw on error)
// tokenizing based on whitespaces (istringstream?)
// 
// then for each token:
// 	if a token is one char and a digit - push token - '0', 
// 	else if one char and operator:
// a) size less than 2 values - underflow - throw
// b) pop two numbers: pop extracts one on the top, so it's 'b', and the 2nd is 'a', meaning a-b or a/b (order matters)  
// overflow due to chain of '*'
// check division by 0 - throw
// apply operator, push result
// 	else reject
// if size != 1 - leftover (throw)
// return top

#endif
