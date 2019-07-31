#pragma once
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
    std::map<char, std::vector<AnagramDerivativeNode*>> mapOfChildsVectorsByLetter;

    AnagramDerivativeNode(const std::string& base, AnagramDerivativeNode* parent = nullptr);
    std::string toString();
    std::vector<AnagramDerivativeNode*> findLongest();
    void addAnagramDerivatives(const char letter, const std::set<std::string>& anagrams);
};






