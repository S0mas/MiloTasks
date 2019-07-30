#pragma once
#include <string>
#include <vector>
#include <map>
#include "DictionaryParser.h"
#include "wordsbasemap.h"
#include "anagramderivative.h"
#include <stack>


class AnagramDerivationAlg {
    DictionaryParser parser;
    WordsBaseMap wordsBaseMap;
    const std::vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    bool isDerivation(const std::string& candidate, const std::string& base) const noexcept {
        return false;
    }

    std::set<std::string> findAnagrams(const std::string& word) noexcept {
        return wordsBaseMap.getAnagrams(word);
    }

    void createBiggerAnagrams(AnagramDerivative* anagramDerivative) noexcept {
        for(auto const& letter : letters) {
            auto const& biggerAnagrams = findAnagrams(anagramDerivative->base+letter);
            for(auto const& anagram : biggerAnagrams){
               anagramDerivative->biggerAnagrams.push_back(new AnagramDerivative(anagram));
            }
        }
    }
    bool findAnagramDerivationHelper(std::stack<AnagramDerivative*>& nodesStack) noexcept {
        if(nodesStack.empty())
           return false;
        auto root = nodesStack.top();
        nodesStack.pop();
        createBiggerAnagrams(root);
        if(!root->biggerAnagrams.empty())
            nodesStack.push(root->biggerAnagrams.back());
        return true;
    }

public:
    AnagramDerivative* findAnagramDerivation(const std::string& base) noexcept {
        auto result = new AnagramDerivative(base);
        std::stack<AnagramDerivative*> toCalculate;
        toCalculate.push(result);
        while(findAnagramDerivationHelper(toCalculate)){
            std::cout << ".";
        }
        return result;
    }

    void createWordBaseFromFile(const std::string& fileName) {
        auto dictionary = parser.parseDictionaryFromFile(fileName);
        for(auto& word : dictionary)
            wordsBaseMap.addWord(std::move(word));
    }
};
