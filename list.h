#pragma once
#include <iostream>
#include <stdexcept>
#include <random>
#include <unordered_set>


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

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear_list();
            copy_list(other);
        }
        return *this;
    }
    
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
    
    void push_tail(const LinkedList& other) {
        Node<T>* current = other.head;
        while (current) {
            push_tail(current->data);
            current = current->next;
        }
    }
    
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
    
    void push_head(const LinkedList& other) {
        LinkedList<T> temp(other);
        Node<T>* current = temp.head;
        while (current) {
            push_head(current->data);
            current = current->next;
        }
    }

    void pop_tail() {
        if (!tail) throw std::underflow_error("List is empty.");
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        }
        else {
            Node<T>* current = head;
            while (current->next != tail) {
                current = current->next;
            }
            delete tail;
            tail = current;
            tail->next = nullptr;
        }
        --size;
    }
    
    void delete_node(T value) {
        while (head && head->data == value) {
            pop_head();
        }
        Node<T>* current = head;
        while (current && current->next) {
            if (current->next->data == value) {
                Node<T>* temp = current->next;
                current->next = current->next->next;
                delete temp;
                --size;
            }
            else {
                current = current->next;
            }
        }
        if (tail && tail->data == value) {
            pop_tail();
        }
    }

    T operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range.");
        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }
    
    T& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range.");
        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }
    
    size_t get_size() const {
        return size;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const LinkedList& list) {
        Node<T>* current = list.head;
        while (current) {
            os << current->data << " ";
            current = current->next;
        }
        return os;
    }
};
