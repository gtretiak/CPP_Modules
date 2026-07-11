#include <iostream>
#include "Array.hpp"
#include <ctime>
#include <cstdlib>

#define MAX_VAL 5
int main(int, char**)
{
    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    std::cout << "Generating values...\n"; 
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
	std::cout << "value " << i + 1 << ": " << value << std::endl;
	numbers[i] = value;
        mirror[i] = value;
    }
    std::cout << "\nCopy constructor and copy assignment testing...";
    Array<int> tmp = numbers;
    Array<int> test(tmp);
    std::cout << "Copies created successfully.\nComparing values...";
    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i] || tmp[i] != numbers[i] || test[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    std::cout << "Values match.\n\n";
    std::cout << "Out of bounds reach attempts (test for exceptions)...\n";
    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << " : Index out of bounds" << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << " : Index out of bounds" << '\n';
    }
    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }
    std::cout << "\nDeallocating memory slots...\n";
    delete [] mirror;//
    return 0;
}
