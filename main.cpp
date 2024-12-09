#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <functional>

struct stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

stats insertion_sort(std::vector<int>& arr) {
    stats stat;
    size_t n = arr.size();
    for (size_t i = 1; i < n; ++i) {
        int key = arr[i];
        ++stat.copy_count;
        size_t j = i;
        while (j > 0 && arr[j - 1] > key) {
            ++stat.comparison_count;
            arr[j] = arr[j - 1];
            ++stat.copy_count; 
            --j;
        }
        if (j > 0) ++stat.comparison_count;
        arr[j] = key;
        ++stat.copy_count;
    }
    return stat;
}

