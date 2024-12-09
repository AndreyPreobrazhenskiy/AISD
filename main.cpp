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

stats shell_sort(std::vector<int>& arr) {
    stats stat;
    size_t n = arr.size();
    for (size_t gap = n / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < n; ++i) {
            int temp = arr[i];
            ++stat.copy_count; // Считаем копирование
            size_t j = i;
            while (j >= gap && arr[j - gap] > temp) {
                ++stat.comparison_count; // Сравнение
                arr[j] = arr[j - gap];
                ++stat.copy_count; // Копирование
                j -= gap;
            }
            if (j >= gap) ++stat.comparison_count; // Последнее сравнение
            arr[j] = temp;
            ++stat.copy_count; // Копирование temp
        }
    }
    return stat;
}
