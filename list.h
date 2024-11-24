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

    // Оператор присваивания
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear_list();
            copy_list(other);
        }
        return *this;
    }
    
    // Добавление элемента в конец
    void push_tail(T value) {
        Node<T>* new_node = new Node<T>(value);
        if (!tail) {
            head = tail = new_node;
        }
        else {
            tail->next = new_node;
            tail = new_node;
        }
        ++size;
    }
    
    // Перегруженный метод: добавление другого списка в конец
    void push_tail(const LinkedList& other) {
        Node<T>* current = other.head;
        while (current) {
            push_tail(current->data);
            current = current->next;
        }
    }
    
    // Добавление элемента в начало
    void push_head(T value) {
        Node<T>* new_node = new Node<T>(value);
        if (!head) {
            head = tail = new_node;
        }
        else {
            new_node->next = head;
            head = new_node;
        }
        ++size;
    }
    
    // Перегруженный метод: добавление другого списка в начало
    void push_head(const LinkedList& other) {
        LinkedList<T> temp(other);
        Node<T>* current = temp.head;
        while (current) {
            push_head(current->data);
            current = current->next;
        }
    }

};
