#include "anagramderivativenode.h"
#include "anagramstringhash.h"
#include <algorithm>
#include <cstdint>

void AnagramDerivativeNode::toStringHelper(std::string &result, const AnagramDerivativeNode *node) {
    if(node->parent != nullptr){
        toStringHelper(result, node->parent);
        result += " + ";
        result.push_back(node->differenceBetweenParent);
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

AnagramDerivativeNode::AnagramDerivativeNode(const std::string &base, AnagramDerivativeNode* parent, const char differenceBetweenParent)
    : baseWord(base), parent(parent), differenceBetweenParent(differenceBetweenParent) {
}

AnagramDerivativeNode::~AnagramDerivativeNode() {
    for(auto const& map : mapOfChildsVectorsByLetter)
        for(auto const& node : map.second)
            delete node;
    mapOfChildsVectorsByLetter.clear();
}

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

void AnagramDerivativeNode::addAnagramDerivatives(const char letter, const AnagramsBase::AnagramsSet& anagrams) {
    std::vector<AnagramDerivativeNode*> v;
    v.reserve(anagrams.size());
    std::transform(anagrams.begin(), anagrams.end(), std::back_inserter(v),
                   [this, letter](const std::string* anagram) -> AnagramDerivativeNode* { return new AnagramDerivativeNode(*anagram, this, letter); });
    mapOfChildsVectorsByLetter[letter] = v;
}
