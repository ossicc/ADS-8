// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>

template <typename T>
class BST {
 public:
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;

    explicit Node(T k)
        : key(k),
          count(1),
          left(nullptr),
          right(nullptr) {}
  };

 private:
  Node* root;

  Node* insert(Node* node, T value) {
    if (!node) return new Node(value);

    if (value == node->key) {
      node->count++;
    } else if (value < node->key) {
      node->left = insert(node->left, value);
    } else {
      node->right = insert(node->right, value);
    }

    return node;
  }

  Node* search(Node* node, T value) const {
    if (!node || node->key == value) {
      return node;
    }

    if (value < node->key) {
      return search(node->left, value);
    } else {
      return search(node->right, value);
    }
  }

  int depth(Node* node) const {
    if (!node) return -1;
    int leftDepth = depth(node->left);
    int rightDepth = depth(node->right);
    return 1 + std::max(leftDepth, rightDepth);
  }

  void clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
  }

  template <typename Func>
  void inOrder(Node* node, Func visit) const {
    if (!node) return;
    inOrder(node->left, visit);
    visit(node);
    inOrder(node->right, visit);
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { clear(root); }

  void insert(T value) { root = insert(root, value); }

  int search(T value) const {
    Node* node = search(root, value);
    return node ? node->count : 0;
  }

  int depth() const { return depth(root); }

  template <typename Func>
  void inOrder(Func visit) const {
    inOrder(root, visit);
  }
};

#endif  // INCLUDE_BST_H_
