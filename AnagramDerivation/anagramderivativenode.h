#pragma once
#include "anagramsbase.h"
#include <map>
#include <set>
#include <string>
#include <vector>

class AnagramDerivativeNode {
    void toStringHelper(std::string& result, const AnagramDerivativeNode* node);
    void findBiggestHelper(size_t& depth, const AnagramDerivativeNode* node, std::vector<AnagramDerivativeNode*>& result);
public:
    const std::string baseWord;
    const AnagramDerivativeNode* parent;
    const char differenceBetweenParent;
    std::map<char, std::vector<AnagramDerivativeNode*>> mapOfChildsVectorsByLetter;

    AnagramDerivativeNode(const std::string& base, AnagramDerivativeNode* parent = nullptr, const char differenceBetweenParent = ' ');
    ~AnagramDerivativeNode();
    AnagramDerivativeNode(const AnagramDerivativeNode& anagram) = delete;
    AnagramDerivativeNode(const AnagramDerivativeNode&& anagram) = delete;
    AnagramDerivativeNode& operator=(const AnagramDerivativeNode& anagram) = delete;
    AnagramDerivativeNode& operator=(AnagramDerivativeNode&& anagram) = delete;

    std::string toString();
    std::vector<AnagramDerivativeNode*> findLongest();
    void addAnagramDerivatives(const char letter, const AnagramsBase::AnagramsSet& anagrams);
};






