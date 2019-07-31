#pragma once
#include "logger.h"
#include <array>
#include <set>
#include <string>
#include <cstdint>
#include <cmath>

class AnagramStringHash {
    inline static constexpr std::array<uint8_t, 26> primes = { 3, 59, 29, 37, 2, 61, 53, 47, 7, 97,
                                                           73, 23, 43, 17, 11, 41, 101, 5, 19, 13,
                                                           31, 79, 71, 83, 67, 89};
    inline static std::multiset<uint8_t> primeFactors(uint64_t number) {
        if(!warnedAboutPerformance){
            Logger::warning("Long words detected. Program needs to use more complicated hash function and will be much slower.");
            warnedAboutPerformance = true;
        }
        std::multiset<uint8_t> set;
        for(auto const& prime : primes){
            if(number != 1){
                while(number % prime == 0){
                    set.insert(prime);
                    number /= prime;
                }
            }
        }

        return set;
    }

    inline static std::multiset<uint8_t> handle64BitsOverflow(const uint64_t number) {
        return primeFactors(number);
    }
public:
    inline static bool warnedAboutPerformance = false;
    using Hash = std::pair<uint64_t, std::multiset<uint8_t>>;
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
};
