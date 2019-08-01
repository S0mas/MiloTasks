#pragma once
#include "anagramstringhash.h"
#include <map>
#include <set>

class AnagramsBase {
public:
    using AnagramsSet = std::set<const std::string*>;
    using AnagramsSetsContainer = std::map<AnagramStringHash::Hash, AnagramsSet>;
private:
    AnagramsSetsContainer container;
    void addWord(const std::string& word);
    void clear() noexcept;
public:
    AnagramsBase();
    void refill(const std::string& fileName);
    AnagramsSet& getAnagrams(const std::string& word);
};
