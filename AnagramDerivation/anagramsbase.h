#pragma once
#include "anagramstringhash.h"
#include <cstdint>
#include <map>
#include <set>
#include <string>

class AnagramsBase {
    std::map<AnagramStringHash::Hash, std::set<std::string>> container1;
    std::map<AnagramStringHash::SimpleHash, std::set<std::string>> container2;
    void addWord(std::string&& word);
    void clear() noexcept;
public:
    AnagramsBase();
    void refill(const std::string& fileName, const unsigned aproxlinesNo);
    std::set<std::string>& getAnagrams(const std::string& word);
};
