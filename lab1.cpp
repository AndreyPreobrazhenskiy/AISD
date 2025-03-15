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

int main() {
    const size_t sizes[] = { 1000, 10000, 100000 };
    const size_t num_tests = 1000;
    const size_t num_testz = 100;

    std::cout << "Demo of BST operations:\n";
    BinarySearchTree demo_bst;

    std::cout << "Inserting elements: 10, 20, 30, 5, 15\n";
    demo_bst.insert(10);
    demo_bst.insert(20);
    demo_bst.insert(30);
    demo_bst.insert(5);
    demo_bst.insert(15);

    std::cout << "BST after insertions: ";
    demo_bst.print();

    std::cout << "-----------------------------------------------------------------------" << "\n";

    // Find elements
    std::cout << "Checking if 15 is in the BST: " << (demo_bst.contains(15) ? "Yes" : "No") << "\n";
    std::cout << "Checking if 100 is in the BST: " << (demo_bst.contains(100) ? "Yes" : "No") << "\n";

    std::cout << "-----------------------------------------------------------------------" << "\n";
    // Erase an element
    std::cout << "Erasing element 20\n";
    demo_bst.erase(20);
    std::cout << "BST after erasing 20: ";
    demo_bst.print();

    std::cout << "-----------------------------------------------------------------------" << "\n";

    // Erase an element not present
    std::cout << "Trying to erase element 100 (not in BST)\n";
    demo_bst.erase(100);
    std::cout << "BST after attempting to erase 100: ";
    demo_bst.print();
    std::cout << "-----------------------------------------------------------------------" << "\n";

    BinarySearchTree tst_bst;
    tst_bst.insert(10);
    tst_bst.insert(20);
    tst_bst.insert(10);
    std::cout << "Checking the duplicate criterion of BST (inserted 10, 20, 10): ";
    tst_bst.print();

    std::cout << "=======================================================================" << "\n";

    for (size_t size : sizes) {
        BinarySearchTree bst;
        std::vector<int> vec;

        //BinarySearchTree test
        auto start = std::chrono::high_resolution_clock::now();
        testInsert(bst, size);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> bst_insert_duration = end - start;

        start = std::chrono::high_resolution_clock::now();
        testFind(bst, num_tests);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> bst_find_duration = end - start;

        start = std::chrono::high_resolution_clock::now();
        testErase(bst, num_tests);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> bst_erase_duration = end - start;

        //std::vector<int> test
        start = std::chrono::high_resolution_clock::now();
        testVectorInsert(vec, size);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> vec_insert_duration = end - start;

        start = std::chrono::high_resolution_clock::now();
        testVectorFind(vec, num_tests);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> vec_find_duration = end - start;

        start = std::chrono::high_resolution_clock::now();
        testVectorErase(vec, num_tests);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> vec_erase_duration = end - start;

        std::cout << "Size: " << size << "\n";
        std::cout << "BinarySearchTree:\n";
        std::cout << "  Insert: " << bst_insert_duration.count() / num_testz << "s per test\n";
        std::cout << "  Find: " << bst_find_duration.count() / num_tests << "s per test\n";
        std::cout << "  Erase: " << bst_erase_duration.count() / num_tests << "s per test\n";
        std::cout << "std::vector<int>:\n";
        std::cout << "  Insert: " << vec_insert_duration.count() / num_testz << "s per test\n";
        std::cout << "  Find: " << vec_find_duration.count() / num_tests << "s per test\n";
        std::cout << "  Erase: " << vec_erase_duration.count() / num_tests << "s per test\n";
        std::cout << "-----------------------------------------------------------------------\n";
    }

    std::cout << "=======================================================================" << "\n";

    std::vector<int> nums = { 3, 2, 2, 4, 2 };
    std::vector<int> result = findUniqueElements(nums);

    std::cout << "Task function\n";
    std::cout << "Unique elements: ";
    for (int num : result) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
