#include <iostream>
#include <vector>
#include <random>
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

stats shell_sort(std::vector<int>& arr) {
    stats stat;
    size_t n = arr.size();
    for (size_t gap = n / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < n; ++i) {
            int temp = arr[i];
            ++stat.copy_count; 
            size_t j = i;
            while (j >= gap && arr[j - gap] > temp) {
                ++stat.comparison_count; 
                arr[j] = arr[j - gap];
                ++stat.copy_count; 
                j -= gap;
            }
            if (j >= gap) ++stat.comparison_count; 
            arr[j] = temp;
            ++stat.copy_count; 
        }
    }
    return stat;
}

void heapify(std::vector<int>& arr, size_t n, size_t i, stats& stat) {
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
        ++stat.comparison_count;
    }
    else if (left < n) {
        ++stat.comparison_count;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
        ++stat.comparison_count;
    }
    else if (right < n) {
        ++stat.comparison_count;
    }

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        stat.copy_count += 3; 
        heapify(arr, n, largest, stat);
    }
}

stats heap_sort(std::vector<int>& arr) {
    stats stat;
    size_t n = arr.size();

    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i, stat);
    }

    for (int i = n - 1; i >= 0; --i) {
        std::swap(arr[0], arr[i]);
        stat.copy_count += 3; 
        heapify(arr, i, 0, stat);
    }
    return stat;
}

std::vector<int> generate_random_array(size_t size, unsigned seed) {
    std::vector<int> arr(size);
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist(0, 10000);
    for (auto& val : arr) {
        val = dist(gen);
    }
    return arr;
}

std::vector<int> generate_sorted_array(size_t size) {
    std::vector<int> arr(size);
    for (size_t i = 0; i < size; ++i) {
        arr[i] = i;
    }
    return arr;
}

std::vector<int> generate_reverse_sorted_array(size_t size) {
    std::vector<int> arr(size);
    for (size_t i = 0; i < size; ++i) {
        arr[i] = size - i;
    }
    return arr;
}
