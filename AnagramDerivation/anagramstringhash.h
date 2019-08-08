#pragma once
#include "logger.h"
#include <array>
#include <cstdint>
#include <string>

class AnagramStringHash {
    inline static constexpr std::array<uint8_t, 26> primes = { 3, 59, 29, 37, 2, 61, 53, 47, 7, 97,
                                                           73, 23, 43, 17, 11, 41, 101, 5, 19, 13,
                                                           31, 79, 71, 83, 67, 89};
public:
    using OverflowCycles = uint64_t;
    using SimpleHash = uint64_t;
    using Hash = std::pair<OverflowCycles, SimpleHash>;

    inline static uint8_t letterToPrime(const char& letter) {
        return primes.at(static_cast<uint8_t>(letter)-0x61);
    }
    /*!
     * The number of cycles is very small compared to prime product
     * so there is really small chance for collision with normal english dictionary for example.
     * However, instead of unordered_map with this hash function, normal map can be used (it is container that is commented in anagrambase.h file)
     */
    inline size_t operator()(const Hash& hash) const noexcept {
        return hash.first + hash.second;
    }

    inline static Hash cyclicHash(const std::string& word) {
        Hash result = {0, 1};
        for(auto const& letter : word){
            auto tmp = result.second;
            result.second *= letterToPrime(letter);
            //OVERFLOW TEST
            if(tmp > result.second)
                ++result.first;
        }
        return result;
    }
};
