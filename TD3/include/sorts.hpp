#pragma once
#include <vector>
#include <algorithm>
#include <iostream>

void bubble_sort(std::vector<int> &vec);

size_t quick_sort_partition(std::vector<int> &vec, size_t left, size_t right);

void quick_sort(std::vector<int> &vec, size_t const left, size_t const right);

void quick_sort(std::vector<int> &vec);

bool is_sorted(std::vector<int> const &vec);
