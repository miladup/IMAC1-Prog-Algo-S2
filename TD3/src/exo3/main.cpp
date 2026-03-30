#include <vector>
#include <cstdlib>
#include <algorithm>
#include "ScopedTimer.hpp"
#include "sorts.hpp"

std::vector<int> generate_random_vector(size_t const size, int const max = 100)
{
    std::vector<int> vec(size);
    std::generate(vec.begin(), vec.end(), [&max]()
                  { return std::rand() % max; });
    return vec;
}

int main()
{
    const size_t size = 100000;

       std::vector<int> original = generate_random_vector(size);

    std::vector<int> v1 = original;
    std::vector<int> v2 = original;
    std::vector<int> v3 = original;

    {
        ScopedTimer timer("std::sort");
        std::sort(v1.begin(), v1.end());
    }

    {
        ScopedTimer timer("bubble_sort");
        bubble_sort(v2);
    }
    {
        ScopedTimer timer("quick_sort");
        quick_sort(v3);
    }

    return 0;
}