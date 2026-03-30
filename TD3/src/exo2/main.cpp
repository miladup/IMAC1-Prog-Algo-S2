#include <vector>
#include <algorithm>
#include <iostream>
#include "sorts.hpp"

size_t quick_sort_partition(std::vector<int> &vec, size_t left, size_t right)
{
    int pivot = vec[right]; // pivot = dernier élément
    size_t i = left;        // premier élément potentiellement > pivot

    for (size_t j = left; j < right; ++j)
    {
        if (vec[j] < pivot)
        {
            std::swap(vec[i], vec[j]);
            i++;
        }
    }

    // placer le pivot à sa position finale
    std::swap(vec[i], vec[right]);

    return i; // index du pivot
}

void quick_sort(std::vector<int> &vec, size_t const left, size_t const right)
{
    if (left >= right)
        return;

    size_t index_pivot = quick_sort_partition(vec, left, right);

    if (index_pivot > 0)
        quick_sort(vec, left, index_pivot - 1);
    quick_sort(vec, index_pivot + 1, right);
}

void quick_sort(std::vector<int> &vec)
{
    if (!vec.empty())
        quick_sort(vec, 0, vec.size() - 1);
}

bool is_sorted(std::vector<int> const &vec) { return std::is_sorted(vec.begin(), vec.end()); }
