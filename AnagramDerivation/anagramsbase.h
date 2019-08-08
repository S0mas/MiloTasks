#pragma once
#include "anagramstringhash.h"
#include <map>
#include <unordered_map>
#include <set>

class AnagramsBase {
public:
    using AnagramsSet = std::set<const std::string*>;
    //using AnagramsSetsContainer = std::map<AnagramStringHash::Hash, AnagramsSet>;
    using AnagramsSetsContainer2 = std::unordered_map<AnagramStringHash::Hash, AnagramsSet, AnagramStringHash>;
private:
    //AnagramsSetsContainer container;
    AnagramsSetsContainer2 container2;
    void addWord(const std::string& word);
    void clear() noexcept;
public:
    AnagramsBase();
    void refill(const std::string& fileName);
    AnagramsSet& getAnagrams(const std::string& word);
};
