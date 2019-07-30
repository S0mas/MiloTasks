#pragma once
#include <string>
#include <vector>

struct AnagramDerivative {
    const std::string base;
    std::vector<AnagramDerivative*> biggerAnagrams;

    AnagramDerivative(const std::string& base) : base(base) {
        biggerAnagrams.reserve(100);
    }
};
