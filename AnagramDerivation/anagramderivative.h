#pragma once
#include <map>
#include <string>
#include <vector>

struct AnagramDerivative {
    const std::string base;
    std::map<char, std::vector<AnagramDerivative*>> biggerAnagrams;
    AnagramDerivative* parent = nullptr;
    AnagramDerivative(const std::string& base) : base(base) {}
};
