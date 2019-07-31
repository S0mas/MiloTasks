#pragma once
#include "logger.h"
#include <array>
#include <set>
#include <string>
#include <cstdint>
#include <cmath>
#include <optional>
#include <map>

class AnagramStringHash {
    inline static std::map<uint64_t, std::multiset<uint8_t>> cachedPrimeFactorizations;
    inline static constexpr std::array<uint8_t, 26> primes = { 3, 59, 29, 37, 2, 61, 53, 47, 7, 97,
                                                           73, 23, 43, 17, 11, 41, 101, 5, 19, 13,
                                                           31, 79, 71, 83, 67, 89};
    inline static std::multiset<uint8_t> primeFactors(const uint64_t number) {
        auto toFactorize = number;
        if(cachedPrimeFactorizations.find(number) == cachedPrimeFactorizations.end()){
            std::multiset<uint8_t> set;
            for(auto const& prime : primes){
                if(toFactorize != 1){
                    while(toFactorize % prime == 0){
                        set.insert(prime);
                        toFactorize /= prime;
                    }
                }
            }
            cachedPrimeFactorizations[number] = set;
            return set;
        }
        return cachedPrimeFactorizations[number];

    }

    inline static std::multiset<uint8_t> handle64BitsOverflow(const uint64_t number) {
        return primeFactors(number);
    }
public:
    inline static bool canSimpleHashBeUsed = true;
    using Hash = std::pair<uint64_t, std::multiset<uint8_t>>;
    using SimpleHash = uint64_t;

    inline static uint8_t letterToPrime(const char& letter) {
        return primes.at(static_cast<uint8_t>(letter)-0x61);
    }

    inline static char primeToLetter(const uint8_t& toFind) {
        for(auto i = 0u; i < primes.size(); ++i)
            if(primes[i] == toFind)
                return static_cast<char>(0x61 + i);
        throw std::runtime_error("Error! This prime number is not mapped to any letter");
    }

    inline static Hash hash(const std::string& word) {
        Hash result = {1, {}};
        for(auto const& letter : word){
            if(result.second.empty()) {
                auto tmp = result.first;
                result.first *= letterToPrime(letter);
                //handle for longer words
                if(tmp > result.first){
                    result.second = handle64BitsOverflow(tmp);
                    result.second.insert(letterToPrime(letter));
                    result.first = 0;
                }
            }
            else
                result.second.insert(letterToPrime(letter));
        }

        return result;
    }

    inline static std::optional<SimpleHash> simpleHash(const std::string& word) {
        SimpleHash result = 1;
        for(auto const& letter : word){
            auto tmp = result;
            result *= letterToPrime(letter);
            if(tmp > result)
                return {0};
        }
        return result;
    }
};
