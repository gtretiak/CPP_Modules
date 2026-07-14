#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <exception>
#include "easyfind.hpp"

template <typename T>
void testContainer(const std::string& name, T& container, int value)
{
    std::cout << "Searching for " << value << " in " << name << ": ";
    try
    {
        typename T::iterator it = easyfind(container, value);
        std::cout << "Found (" << *it << ")" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

template <typename T>
void testConstContainer(const std::string& name, const T& container, int value)
{
    std::cout << "Searching for " << value << " in const " << name << ": ";
    try
    {
        typename T::const_iterator it = easyfind(container, value);
        std::cout << "Found (" << *it << ")" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

int main(void)
{
    std::cout << "==========================================" << std::endl;
    std::cout << "VECTOR TESTS {1,5,7,5,10,-42}" << std::endl;
    std::cout << "==========================================" << std::endl;

    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(5);
    vec.push_back(7);
    vec.push_back(5);
    vec.push_back(10);
    vec.push_back(-42);

    testContainer("vector", vec, 1);       // first
    testContainer("vector", vec, 7);       // middle
    testContainer("vector", vec, 10);      // last
    testContainer("vector", vec, 5);       // duplicate
    testContainer("vector", vec, -42);     // negative
    testContainer("vector", vec, 100);     // absent

    std::cout << std::endl;

    const std::vector<int> cvec(vec);

    testConstContainer("vector", cvec, 1);
    testConstContainer("vector", cvec, 7);
    testConstContainer("vector", cvec, 10);
    testConstContainer("vector", cvec, 5);
    testConstContainer("vector", cvec, -42);
    testConstContainer("vector", cvec, 100);

    std::cout << std::endl;

    std::vector<int> emptyVec;
    testContainer("empty vector", emptyVec, 1);

    std::vector<int> oneVec;
    oneVec.push_back(42);
    std::cout << std::endl;

    testContainer("one-element vector", oneVec, 42);
    testContainer("one-element vector", oneVec, 0);

    std::cout << "\n==========================================" << std::endl;
    std::cout << "LIST TESTS {1,5,7,5,10,-42}" << std::endl;
    std::cout << "==========================================" << std::endl;

    std::list<int> lst;
    lst.push_back(1);
    lst.push_back(5);
    lst.push_back(7);
    lst.push_back(5);
    lst.push_back(10);
    lst.push_back(-42);

    testContainer("list", lst, 1);
    testContainer("list", lst, 7);
    testContainer("list", lst, 10);
    testContainer("list", lst, 5);
    testContainer("list", lst, -42);
    testContainer("list", lst, 100);

    std::cout << std::endl;

    const std::list<int> clst(lst);

    testConstContainer("list", clst, 1);
    testConstContainer("list", clst, 7);
    testConstContainer("list", clst, 10);
    testConstContainer("list", clst, 5);
    testConstContainer("list", clst, -42);
    testConstContainer("list", clst, 100);

    std::cout << std::endl;

    std::list<int> emptyList;
    testContainer("empty list", emptyList, 1);

    std::list<int> oneList;
    oneList.push_back(100);
    std::cout << std::endl;

    testContainer("one-element list", oneList, 100);
    testContainer("one-element list", oneList, 99);

    std::cout << "\n==========================================" << std::endl;
    std::cout << "DEQUE TESTS {1,5,7,5,10,-42}" << std::endl;
    std::cout << "==========================================" << std::endl;

    std::deque<int> deq;
    deq.push_back(1);
    deq.push_back(5);
    deq.push_back(7);
    deq.push_back(5);
    deq.push_back(10);
    deq.push_back(-42);

    testContainer("deque", deq, 1);
    testContainer("deque", deq, 7);
    testContainer("deque", deq, 10);
    testContainer("deque", deq, 5);
    testContainer("deque", deq, -42);
    testContainer("deque", deq, 100);

    std::cout << std::endl;

    const std::deque<int> cdeq(deq);

    testConstContainer("deque", cdeq, 1);
    testConstContainer("deque", cdeq, 7);
    testConstContainer("deque", cdeq, 10);
    testConstContainer("deque", cdeq, 5);
    testConstContainer("deque", cdeq, -42);
    testConstContainer("deque", cdeq, 100);

    std::cout << std::endl;

    std::deque<int> emptyDeque;
    testContainer("empty deque", emptyDeque, 5);

    std::deque<int> oneDeque;
    oneDeque.push_back(-500);
    std::cout << std::endl;

    testContainer("one-element deque", oneDeque, -500);
    testContainer("one-element deque", oneDeque, 0);

    std::cout << "\n==========================================" << std::endl;
    std::cout << "ALL TESTS FINISHED" << std::endl;
    std::cout << "==========================================" << std::endl;

    return 0;
}
