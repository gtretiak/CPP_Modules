#include <iostream>
#include "Span.hpp"
#include <vector>
#include <list>
#include <deque>

static void printSpan(const Span& sp)
{
    try
    {
        std::cout << "Shortest span: "
                  << sp.shortestSpan() << std::endl;

        std::cout << "Longest span : "
                  << sp.longestSpan() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << std::endl;
}

int main()
{
    std::cout << "========== SUBJECT TEST ==========\n";
    Span sp(100000);
    try
    {
	    for (int i = 0; i < 100000; i++)
		    sp.addNumber(i);
    }
    catch (const std::exception &e)
    {
	    std::cout << e.what() << std::endl;
    }
    printSpan(sp);
    std::cout << "========== VECTOR ==========\n";
    std::vector<int> vec;
    Span vspan(5);
    try
    {
	    vec.push_back(6);
	    vec.push_back(3);
	    vec.push_back(17);
	    vec.push_back(9);
	    vec.push_back(11);
	    vspan.addRange(vec.begin(), vec.end());
    }
    catch (const std::exception &e)
    {
	    std::cout << e.what() << std::endl;
    }
    printSpan(vspan);
    std::cout << "========== LIST ==========\n";
    Span lspan(5);
    std::list<int> lst;
    try
    {
	    lst.push_back(6);
	    lst.push_back(3);
	    lst.push_back(17);
	    lst.push_back(9);
	    lst.push_back(11);
	    lspan.addRange(lst.begin(), lst.end());
    }
    catch (const std::exception &e)
    {
	    std::cout << e.what() << std::endl;
    }
    printSpan(lspan);
    std::cout << "========== DEQUE ==========\n";
    std::deque<int> deq;
    Span dspan(5);
    try
    {
	    deq.push_back(6);
	    deq.push_back(3);
	    deq.push_back(17);
	    deq.push_back(9);
	    deq.push_back(11);
	    dspan.addRange(deq.begin(), deq.end());
    }
    catch (const std::exception &e)
    {
	    std::cout << e.what() << std::endl;
    }
    printSpan(dspan);
    std::cout << "========== OVERFLOW ==========\n";
    try
    {
        Span small(3);
        small.addRange(vec.begin(), vec.end());
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n========== NOT ENOUGH NUMBERS ==========\n";
    try
    {
        Span one(10);
        one.addNumber(42);
        std::cout << one.shortestSpan() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}
