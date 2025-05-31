// Copyright 2021 NNTU-CS
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "bst.h"

void populateTreeFromFile(BST<std::string>& tree, const char* filePath) {
  std::ifstream inputFile(filePath);
  if (!inputFile.is_open()) return;

  std::string currentWord;
  char character;
  while (inputFile.get(character)) {
    if (std::isalpha(static_cast<unsigned char>(character))) {
      currentWord += std::tolower(static_cast<unsigned char>(character));
    } else {
      if (!currentWord.empty()) {
        tree.insert(currentWord);
        currentWord.clear();
      }
    }
  }
  if (!currentWord.empty()) {
    tree.insert(currentWord);
  }
  inputFile.close();
}

void displayFrequencies(const BST<std::string>& tree) {
  auto frequencyList = tree.toVector();
  std::sort(
      frequencyList.begin(), frequencyList.end(),
      [](const auto& lhs, const auto& rhs) { return lhs.second > rhs.second; });

  if (!std::filesystem::exists("result")) {
    std::filesystem::create_directory("result");
  }

  std::ofstream outputFile("result/freq.txt");
  if (!outputFile.is_open()) {
    std::cerr << "Ошибка при открытии файла для записи." << std::endl;
    return;
  }

  for (const auto& entry : frequencyList) {
    std::cout << entry.first << " - " << entry.second << std::endl;
    outputFile << entry.first << " - " << entry.second << std::endl;
  }
  outputFile.close();
}
