#pragma once
#include "anagramsbase.h"
#include <set>
#include <stack>
#include <string>
#include <vector>

class AnagramDerivativeNode;

class AnagramDerivationSolver {
    AnagramsBase anagramsBase;
    std::set<std::string>& findAnagrams(const std::string& word);
    void createDerivedAnagrams(AnagramDerivativeNode* node);
    bool findAnagramDerivationTreeHelper(std::stack<AnagramDerivativeNode*>& nodesStack);
    AnagramDerivativeNode* findAnagramDerivationTree(const std::string& base);
public:
    void createWordBaseFromFile(const std::string& fileName, const unsigned aproxlinesNo = 85000);
    std::vector<std::string> solve(std::string base);
};
