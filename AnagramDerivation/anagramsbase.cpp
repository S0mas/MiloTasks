#include "anagramsbase.h"
#include "dictionaryparser.h"
#include <utility>
#include <optional>

AnagramsBase::AnagramsBase() {}

void AnagramsBase::refill(const std::string &fileName) {
    clear();
    DictionaryParser::parseDictionaryFromFile(fileName);
    auto const& dictionary = DictionaryParser::dictionary;
    for(auto& word : dictionary)
        addWord(word);
}

void AnagramsBase::addWord(const std::string& word) {
    container[AnagramStringHash::cyclicHash(word)].insert(&word);
}

void AnagramsBase::clear() noexcept {
    container.clear();
}

AnagramsBase::AnagramsSet& AnagramsBase::getAnagrams(const std::string& word) {
    return container[AnagramStringHash::cyclicHash(word)];
}
