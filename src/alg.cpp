// Copyright 2021 NNTU-CS
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "Ошибка открытия файла!" << std::endl;
    return;
  }

  std::string currentWord;
  char ch;
  while (file.get(ch)) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      currentWord += std::tolower(static_cast<unsigned char>(ch));
    } else if (!currentWord.empty()) {
      tree.insert(currentWord);
      currentWord.clear();
    }
  }

  if (!currentWord.empty()) {
    tree.insert(currentWord);
  }
  file.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> words;

  auto collect = [&words](typename BST<std::string>::Node* node) {
    words.emplace_back(node->key, node->count);
  };

  tree.inOrder(collect);

  std::sort(words.begin(), words.end(),
            [](const auto& a, const auto& b) { return a.second > b.second; });

  for (const auto& [word, count] : words) {
    std::cout << word << ": " << count << std::endl;
  }

  std::ofstream out("result/freq.txt");
  for (const auto& [word, count] : words) {
    out << word << ": " << count << std::endl;
  }
  out.close();
}
