#pragma once
#include "anagramstringhash.h"
#include <iostream>

class WordsBaseMap {
    std::map<unsigned long long, std::set<std::string>> container;
public:
    WordsBaseMap() {}

    void addWord(std::string&& word) noexcept {
        container[AnagramStringHash::hash(word)].insert(std::move(word));
    }

    std::set<std::string>& getAnagrams(const std::string& word) noexcept {
        return container[AnagramStringHash::hash(word)];
    }
};
