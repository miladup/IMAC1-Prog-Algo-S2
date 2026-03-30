#include <vector>
#include <algorithm>
#include <iostream>
#include "sorts.hpp"

int main()
{
    std::vector<int> array{1, 2, 4, 8, 5, 6, 7, 8, 1};
    bubble_sort(array);
    for (int k = 0; k < array.size(); k++)
    {
        std::cout << array[k] << std::endl;
    }
    if (is_sorted(array))
    {

        std::cout << "Le tableau est trie" << std::endl;
    }
    else
    {
        std::cout << "Le tableau n'est pas trie" << std::endl;
    }
}