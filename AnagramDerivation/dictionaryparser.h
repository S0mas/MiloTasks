#pragma once
#include "logger.h"

#include <array>
#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <cctype>
#include <string>

class DictionaryParser {
    inline static constexpr std::array<char, 26> letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
public:
    inline static std::optional<char> isStrUsingInvalidChar(const std::string& word) noexcept {
        for(auto const& c : word)
            if(c < 0x61 || c > 0x7A)
                return c;
        return {};
    }

    inline static std::vector<std::string> parseDictionaryFromFile(const std::string& fileName, const unsigned aproxlinesNo) {
        std::vector<std::string> result;
        result.reserve(aproxlinesNo);
        std::ifstream infile(fileName);
        std::string line;
        while (std::getline(infile, line)){
            tolower(line);         
            if(auto c = isStrUsingInvalidChar(line))
                Logger::warning("word: " + std::move(line) + " skipped, it contains unsupported character: " + *c);
            else
                result.push_back(std::move(line));
        }

        return result;
    }

    inline static void tolower(std::string& string) {
        std::transform(string.begin(), string.end(), string.begin(),
            [](unsigned char c){ return std::tolower(c); });
    }

    inline static const std::array<char, 26>& supportedLetters() {
        return letters;
    }
};
