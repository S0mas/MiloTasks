#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class DictionaryParser {
public:
    std::vector<std::string> parseDictionaryFromFile(const std::string& fileName) {
        std::vector<std::string> result;
        result.reserve(85000);
        std::ifstream infile(fileName);
        std::string line;
        while (std::getline(infile, line))
            result.push_back(std::move(line));
        return result;
    }
};
