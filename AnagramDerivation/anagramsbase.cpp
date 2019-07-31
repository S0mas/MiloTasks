#include "anagramsbase.h"
#include "dictionaryparser.h"
#include <utility>

AnagramsBase::AnagramsBase() {}

void AnagramsBase::refill(const std::string &fileName, const unsigned aproxlinesNo) {
    clear();
    auto dictionary = DictionaryParser::parseDictionaryFromFile(fileName, aproxlinesNo);
    for(auto& word : dictionary)
        addWord(std::move(word));
}

void AnagramsBase::addWord(std::string &&word) {
    container[AnagramStringHash::hash(word)].insert(std::move(word));
}

void AnagramsBase::clear() noexcept {
    container.clear();
}

std::set<std::string>& AnagramsBase::getAnagrams(const std::string &word) {
    return container[AnagramStringHash::hash(word)];
}
