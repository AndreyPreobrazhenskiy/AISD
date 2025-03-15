#pragma once
#include <iostream>


class BinarySearchTree {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;

        Node(int val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void destroy(Node* node) {
        if (node) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

    Node* copy(Node* node) {
        if (!node) return nullptr;
        Node* new_node = new Node(node->data);
        new_node->left = copy(node->left);
        new_node->right = copy(node->right);
        return new_node;
    }

    bool insert(Node*& node, int key) {
        if (!node) {
            node = new Node(key);
            return true;
        }
        if (key < node->data) {
            return insert(node->left, key);
        }
        else if (key > node->data) {
            return insert(node->right, key);
        }
        return false; // key already exists
    }

    bool contains(Node* node, int key) const {
        if (!node) return false;
        if (key < node->data) return contains(node->left, key);
        if (key > node->data) return contains(node->right, key);
        return true; // found
    }

    bool erase(Node*& node, int key) {
        if (!node) return false;
        if (key < node->data) return erase(node->left, key);
        if (key > node->data) return erase(node->right, key);

        // Node with the key found, now delete it
        if (!node->left && !node->right) { // No children
            delete node;
            node = nullptr;
        }
        else if (!node->left) { // Only right child
            Node* temp = node;
            node = node->right;
            delete temp;
        }
        else if (!node->right) { // Only left child
            Node* temp = node;
            node = node->left;
            delete temp;
        }
        else { // Two children
            Node* min_larger_node = findMin(node->right);
            node->data = min_larger_node->data;
            erase(node->right, min_larger_node->data);
        }
        return true;
    }
