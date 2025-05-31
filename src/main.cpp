// Copyright 2021 NNTU-CS
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
  const char* filename = "src/war_peace.txt";
  BST<std::string> tree;
  makeTree(tree, filename);
  printFreq(tree);
  return 0;
}
