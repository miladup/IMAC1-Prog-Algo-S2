#include <vector>
#include <cstdlib>
#include <algorithm>
#include "ScopedTimer.hpp"
#include "sorts.hpp"

int search(const std::vector<int> &vec, int value)
{
    int left = 0;
    int right = vec.size() - 1;

    while (left <= right)
    {
        int middle = (left + right) / 2;

        if (vec[middle] == value)
        {
            return middle;
        }
        else if (vec[middle] < value)
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
    }

    return -1;
}
int main()
{
    std::vector<int> vec1{1, 2, 2, 3, 4, 8, 12};
    std::vector<int> vec2{1, 2, 3, 3, 6, 14, 12, 15};
    std::vector<int> vec3{2, 2, 3, 4, 5, 8, 12, 15, 16};
    std::vector<int> vec4{5, 6, 7, 8, 9, 10, 11, 12, 13};
    std::vector<int> vec5{1, 2, 3, 4, 5, 6, 7, 8, 9};

    int index1 = search(vec1, 8);
    int index2 = search(vec2, 15);
    int index3 = search(vec3, 16);
    int index4 = search(vec4, 6);
    int index5 = search(vec5, 10);
    std::cout << index1 << " "
              << index2 << " "
              << index3 << " "
              << index4 << " "
              << index5 << std::endl;
}