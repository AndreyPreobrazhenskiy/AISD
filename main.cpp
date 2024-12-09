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

void random_array_experiment(size_t size, unsigned seed) {
    stats avg_insertion, avg_shell, avg_heap;

    for (int i = 0; i < 100; ++i) {
        std::vector<int> random_array = generate_random_array(size, seed++);
        std::vector<int> arr_copy = random_array;

        stats stats_insertion = insertion_sort(arr_copy);
        avg_insertion.comparison_count += stats_insertion.comparison_count;
        avg_insertion.copy_count += stats_insertion.copy_count;

        stats stats_shell = shell_sort(random_array);
        avg_shell.comparison_count += stats_shell.comparison_count;
        avg_shell.copy_count += stats_shell.copy_count;

        stats stats_heap = heap_sort(random_array);
        avg_heap.comparison_count += stats_heap.comparison_count;
        avg_heap.copy_count += stats_heap.copy_count;
    }

    avg_insertion.comparison_count /= 100;
    avg_insertion.copy_count /= 100;

    avg_shell.comparison_count /= 100;
    avg_shell.copy_count /= 100;

    avg_heap.comparison_count /= 100;
    avg_heap.copy_count /= 100;

    std::cout << "\nRandom Arrays (Size: " << size << ")\n"
        << "  Insertion Sort - Comparisons: " << avg_insertion.comparison_count
        << ", Copies: " << avg_insertion.copy_count << "\n"
        << "  Shell Sort - Comparisons: " << avg_shell.comparison_count
        << ", Copies: " << avg_shell.copy_count << "\n"
        << "  Heap Sort - Comparisons: " << avg_heap.comparison_count
        << ", Copies: " << avg_heap.copy_count << "\n";
}

void sorted_array_experiment(size_t size) {
    std::vector<int> sorted_array = generate_sorted_array(size);

    stats stats_insertion = insertion_sort(sorted_array);
    stats stats_shell = shell_sort(sorted_array);
    stats stats_heap = heap_sort(sorted_array);

    std::cout << "\nSorted Array (Size: " << size << ")\n"
        << "  Insertion Sort - Comparisons: " << stats_insertion.comparison_count
        << ", Copies: " << stats_insertion.copy_count << "\n"
        << "  Shell Sort - Comparisons: " << stats_shell.comparison_count
        << ", Copies: " << stats_shell.copy_count << "\n"
        << "  Heap Sort - Comparisons: " << stats_heap.comparison_count
        << ", Copies: " << stats_heap.copy_count << "\n";
}

void reverse_array_experiment(size_t size) {
    std::vector<int> reverse_array = generate_reverse_sorted_array(size);

    stats stats_insertion = insertion_sort(reverse_array);
    stats stats_shell = shell_sort(reverse_array);
    stats stats_heap = heap_sort(reverse_array);

    std::cout << "\nReverse Sorted Array (Size: " << size << ")\n"
        << "  Insertion Sort - Comparisons: " << stats_insertion.comparison_count
        << ", Copies: " << stats_insertion.copy_count << "\n"
        << "  Shell Sort - Comparisons: " << stats_shell.comparison_count
        << ", Copies: " << stats_shell.copy_count << "\n"
        << "  Heap Sort - Comparisons: " << stats_heap.comparison_count
        << ", Copies: " << stats_heap.copy_count << "\n";
}
