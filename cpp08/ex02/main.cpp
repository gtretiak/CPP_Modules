#include <iostream>
#include "MutantStack.hpp"
#include <list>

int main()
{
    std::cout << "========== BASIC STACK ==========\n";
    MutantStack<int> ms;
    ms.push(5);
    ms.push(17);
    std::cout << "Top: " << ms.top() << std::endl;
    ms.pop();
    std::cout << "Size: " << ms.size() << std::endl;
    ms.push(3);
    ms.push(5);
    ms.push(737);
    ms.push(0);

    std::cout << "\n========== ITERATION ==========\n";
    MutantStack<int>::iterator it = ms.begin();
    MutantStack<int>::iterator ite = ms.end();
    ++it;
    --it;
    while (it != ite)
    {
        std::cout << *it << std::endl;
	it++;
    }

    std::cout << "\n========== COPY CONSTRUCTOR ==========\n";
    MutantStack<int> copy(ms);
    for (MutantStack<int>::iterator it = copy.begin();
         it != copy.end();
         ++it)
    {
        std::cout << *it << std::endl;
    }

    std::cout << "\n========== BASE CLASS COMPATIBILITY ==========\n";
    std::stack<int>	s(ms);
    std::cout << "Test passed\n";

    std::cout << "\n========== ASSIGNMENT ==========\n";
    MutantStack<int> assign;
    assign = ms;
    for (MutantStack<int>::iterator it = assign.begin();
         it != assign.end();
         ++it)
    {
        std::cout << *it << std::endl;
    }

    std::cout << "\n========== MODIFY ORIGINAL ==========\n";
    ms.pop();
    ms.pop();
    std::cout << "Original size: " << ms.size() << std::endl;
    std::cout << "Copy size:     " << copy.size() << std::endl;
    std::cout << "Assigned size: " << assign.size() << std::endl;
    std::cout << "\n========== SUBJECT COMPARISON ==========\n";
    std::list<int> lst;
    lst.push_back(5);
    lst.push_back(3);
    lst.push_back(5);
    lst.push_back(737);
    lst.push_back(0);
    std::cout << "MutantStack:\n";
    for (MutantStack<int>::iterator it = assign.begin();
         it != assign.end();
         ++it)
    {
        std::cout << *it << std::endl;
    }
    std::cout << "\nstd::list:\n";
    for (std::list<int>::iterator it = lst.begin();
         it != lst.end();
         ++it)
    {
        std::cout << *it << std::endl;
    }
}
