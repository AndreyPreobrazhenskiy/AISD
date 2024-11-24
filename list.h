#pragma once
#include <iostream>


template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T value) : data(value), next(nullptr) {}
};


template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    size_t size;

    void copy_list(const LinkedList& other) {
        Node<T>* current = other.head;
        while (current) {
            push_tail(current->data);
            current = current->next;
        }
    }

    void clear_list() {
        while (head) {
            pop_head();
        }
    }

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), size(0) {
        copy_list(other);
    }

    LinkedList(size_t n, T min_val, T max_val) : head(nullptr), tail(nullptr), size(0) {
        std::mt19937 gen(42);
        std::uniform_int_distribution<T> dist(min_val, max_val);

        for (size_t i = 0; i < n; ++i) {
            push_tail(dist(gen));
        }
    }

    ~LinkedList() {
        clear_list();
    }
};
