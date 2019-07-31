#include "anagramsbase.h"
#include "dictionaryparser.h"
#include <utility>
#include <optional>

AnagramsBase::AnagramsBase() {}

void AnagramsBase::refill(const std::string &fileName, const unsigned aproxlinesNo) {
    clear();
    auto dictionary = DictionaryParser::parseDictionaryFromFile(fileName, aproxlinesNo);
    for(auto& word : dictionary)
        addWord(std::move(word));
}

void AnagramsBase::addWord(std::string &&word) {
    if(auto option = AnagramStringHash::simpleHash(word))
        container2[*option].insert(std::move(word));
    else
        container1[AnagramStringHash::hash(word)].insert(std::move(word));
}

void AnagramsBase::clear() noexcept {
    container1.clear();
    container2.clear();
}

std::set<std::string>& AnagramsBase::getAnagrams(const std::string &word) {
    if(auto option = AnagramStringHash::simpleHash(word))
        return container2[*option];
    return container1[AnagramStringHash::hash(word)];
}
