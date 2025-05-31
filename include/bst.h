// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <string>
#include <vector>
#include <utility>
template <typename T>
class BinarySearchTree {
private:
    struct TreeNode {
        T value;
        int occurrences;
        TreeNode* leftChild;
        TreeNode* rightChild;

        TreeNode(const T& val) 
            : value(val), occurrences(1), leftChild(nullptr), rightChild(nullptr) {}
    };

    TreeNode* rootNode;

    void addNode(TreeNode*& currentNode, const T& value) {
        if (currentNode == nullptr) {
            currentNode = new TreeNode(value);
        } else if (value == currentNode->value) {
            currentNode->occurrences++;
        } else if (value < currentNode->value) {
            addNode(currentNode->leftChild, value);
        } else {
            addNode(currentNode->rightChild, value);
        }
    }

    int findOccurrences(TreeNode* currentNode, const T& value) const {
        if (currentNode == nullptr) return 0;
        if (value == currentNode->value) return currentNode->occurrences;
        return value < currentNode->value ? 
               findOccurrences(currentNode->leftChild, value) : 
               findOccurrences(currentNode->rightChild, value);
    }

    int calculateDepth(TreeNode* currentNode) const {
        if (currentNode == nullptr) return 0;
        int leftHeight = calculateDepth(currentNode->leftChild);
        int rightHeight = calculateDepth(currentNode->rightChild);
        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }

    void traverseInOrder(TreeNode* currentNode, std::vector<std::pair<T, int>>& output) const {
        if (currentNode == nullptr) return;
        traverseInOrder(currentNode->leftChild, output);
        output.emplace_back(currentNode->value, currentNode->occurrences);
        traverseInOrder(currentNode->rightChild, output);
    }

    void deleteTree(TreeNode* currentNode) {
        if (currentNode == nullptr) return;
        deleteTree(currentNode->leftChild);
        deleteTree(currentNode->rightChild);
        delete currentNode;
    }

public:
    BinarySearchTree() : rootNode(nullptr) {}

    ~BinarySearchTree() {
        deleteTree(rootNode);
    }

    void insert(const T& value) {
        addNode(rootNode, value);
    }

    int search(const T& value) const {
        return findOccurrences(rootNode, value);
    }

    int depth() const {
        return calculateDepth(rootNode);
    }

    std::vector<std::pair<T, int>> toVector() const {
        std::vector<std::pair<T, int>> output;
        traverseInOrder(rootNode, output);
        return output;
    }
};
#endif  // INCLUDE_BST_H_
