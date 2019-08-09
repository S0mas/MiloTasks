#pragma once
#include "anagramsbase.h"
#include <memory>
#include <set>
#include <stack>
#include <string>
#include <vector>

class AnagramDerivativeNode;

class AnagramDerivationSolver {
    AnagramsBase anagramsBase;
    AnagramsBase::AnagramsSet& findAnagrams(const std::string& word);
    void createDerivedAnagrams(AnagramDerivativeNode* node);
    bool findAnagramDerivationTreeHelper(std::stack<AnagramDerivativeNode*>& nodesStack);
    std::unique_ptr<AnagramDerivativeNode> findAnagramDerivationTree(const std::string& base);
public:
    void createWordBaseFromFile(const std::string& fileName);
    std::vector<std::string> solve(std::string base);
};
