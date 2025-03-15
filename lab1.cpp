#include "lab1.h"
#include <vector>
#include <chrono>
#include <iostream>


size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

template <typename Container>
void testInsert(Container& container, size_t num_elements) {
    for (size_t i = 0; i < num_elements; ++i) {
        container.insert(lcg());
    }
}

template <typename Container>
void testFind(Container& container, size_t num_attempts) {
    for (size_t i = 0; i < num_attempts; ++i) {
        container.contains(lcg());
    }
}

template <typename Container>
void testErase(Container& container, size_t num_attempts) {
    for (size_t i = 0; i < num_attempts; ++i) {
        container.erase(lcg());
    }
}

void testVectorInsert(std::vector<int>& vec, size_t num_elements) {
    for (size_t i = 0; i < num_elements; ++i) {
        vec.push_back(lcg());
    }
}

void testVectorFind(const std::vector<int>& vec, size_t num_attempts) {
    for (size_t i = 0; i < num_attempts; ++i) {
        auto it = std::find(vec.begin(), vec.end(), lcg());
    }
}

void testVectorErase(std::vector<int>& vec, size_t num_attempts) {
    for (size_t i = 0; i < num_attempts; ++i) {
        auto it = std::find(vec.begin(), vec.end(), lcg());
        if (it != vec.end()) {
            vec.erase(it);
        }
    }
}

std::vector<int> findUniqueElements(const std::vector<int>& nums) {
    BinarySearchTree bst;  
    std::vector<int> duplicates; 
    std::vector<int> result; 

    for (int num : nums) {
        if (bst.contains(num)) {
            bst.erase(num);
            duplicates.push_back(num);
        }
        else if (std::find(duplicates.begin(), duplicates.end(), num) == duplicates.end()) {
            bst.insert(num);
        }
    }

    for (int num : nums) {
        if (bst.contains(num)) {
            result.push_back(num);
            bst.erase(num); 
        }
    }

    return result;
}
