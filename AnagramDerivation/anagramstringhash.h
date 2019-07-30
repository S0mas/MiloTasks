#pragma once
#include <map>
#include <string>
#include <set>

class AnagramStringHash {
    inline static const std::map<char, unsigned> lettersToPrimes =  {
        {'e', 2}, {'a', 3}, {'r', 5} , {'i', 7}, {'o', 11}, {'t', 13}, {'n', 17}, {'s', 19}, {'l', 23},
        {'c', 29}, {'u', 31}, {'d', 37}, {'p', 41}, {'m', 43}, {'h', 47}, {'g', 53}, {'b', 59}, {'f', 61},
        {'y', 67}, {'w', 71}, {'k', 73}, {'v', 79}, {'x', 83}, {'z', 89}, {'j', 97}, {'q', 101}
    };

    inline static unsigned mapLetterToPrime(const char& letter) noexcept {
        return lettersToPrimes.at(static_cast<char>(tolower(letter)));
    }
public:
    inline static unsigned long long hash(const std::string& word) noexcept {
        unsigned long long result = 1;
        for(auto const& letter : word)
            result *= mapLetterToPrime(letter);
        return result;
    }
};
