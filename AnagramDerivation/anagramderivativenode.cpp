#include "anagramderivativenode.h"
#include "anagramstringhash.h"
#include <algorithm>
#include <cstdint>

void AnagramDerivativeNode::toStringHelper(std::string &result, const AnagramDerivativeNode *node) {
    if(node->parent != nullptr){
        toStringHelper(result, node->parent);
        result += " + ";
        result.push_back(AnagramStringHash::primeToLetter(static_cast<uint8_t>(2)));
        result += " = ";
    }
    result += node->baseWord;
}

void AnagramDerivativeNode::findBiggestHelper(size_t &depth, const AnagramDerivativeNode *node, std::vector<AnagramDerivativeNode *> &result) {
    for(auto const& map : node->mapOfChildsVectorsByLetter) {
        for(auto const& el : map.second) {
            if(el->baseWord.size() > depth) {
                result.clear();
                depth = el->baseWord.size();
                result.push_back(el);
            }
            else if(el->baseWord.size() == depth)
                result.push_back(el);
            findBiggestHelper(depth, el, result);
        }
    }
}

AnagramDerivativeNode::AnagramDerivativeNode(const std::string &base, AnagramDerivativeNode* parent) : baseWord(base), parent(parent) {}

std::string AnagramDerivativeNode::toString() {
    std::string result;
    toStringHelper(result, this);
    return result;
}

std::vector<AnagramDerivativeNode *> AnagramDerivativeNode::findLongest() {
    size_t depth = 0;
    std::vector<AnagramDerivativeNode*> result;
    findBiggestHelper(depth, this, result);
    return result;
}

void AnagramDerivativeNode::addAnagramDerivatives(const char letter, const std::set<std::string>& anagrams) {
    std::vector<AnagramDerivativeNode*> v;
    v.reserve(anagrams.size());
    std::transform(anagrams.begin(), anagrams.end(), std::back_inserter(v),
                   [this](const std::string& anagram) -> AnagramDerivativeNode* { return new AnagramDerivativeNode(anagram, this); });
    mapOfChildsVectorsByLetter[letter] = v;
}
