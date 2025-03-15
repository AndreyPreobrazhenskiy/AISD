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