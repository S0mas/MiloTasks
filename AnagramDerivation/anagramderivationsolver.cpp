#include "anagramderivativenode.h"
#include "anagramderivationsolver.h"
#include "dictionaryparser.h"
#include "logger.h"

AnagramsBase::AnagramsSet& AnagramDerivationSolver::findAnagrams(const std::string &word) {
    return anagramsBase.getAnagrams(word);
}

void AnagramDerivationSolver::createDerivedAnagrams(AnagramDerivativeNode *node) {
    for(auto const& letter : DictionaryParser::supportedLetters())
        node->addAnagramDerivatives(letter, findAnagrams(node->baseWord+letter));
}

bool AnagramDerivationSolver::findAnagramDerivationTreeHelper(std::stack<AnagramDerivativeNode *> &nodesStack) {
    static unsigned i = 0;
    if(++i % 1000 == 0)
        std::cout << ".";
    if(nodesStack.empty())
        return false;
    auto root = nodesStack.top();
    nodesStack.pop();
    createDerivedAnagrams(root);

    for(auto& anagramsPerLetter : root->mapOfChildsVectorsByLetter)
        if(!anagramsPerLetter.second.empty())
            nodesStack.push(anagramsPerLetter.second.back());
    return true;
}

std::unique_ptr<AnagramDerivativeNode> AnagramDerivationSolver::findAnagramDerivationTree(const std::string& base) {
    auto anagramTreeRoot = std::make_unique<AnagramDerivativeNode>(base);
    std::stack<AnagramDerivativeNode*> toCalculate;
    toCalculate.push(anagramTreeRoot.get());
    while(findAnagramDerivationTreeHelper(toCalculate)){}
    return anagramTreeRoot;
}

void AnagramDerivationSolver::createWordBaseFromFile(const std::string &fileName) {
    Logger::info("Loading dictionary.");
    anagramsBase.refill(fileName);
    Logger::info("Dictionary loaded.");
}

std::vector<std::string> AnagramDerivationSolver::solve(std::string base) {
    Logger::info("Processing");
    DictionaryParser::tolower(base);
    if(auto c = DictionaryParser::isStrUsingInvalidChar(base)) {
        Logger::error("Base anagram " +  base + " contains unsupported character: " + *c);
        return {};
    }
    auto tree = findAnagramDerivationTree(base);
    std::cout << std::endl;
    Logger::info("Searching for results.");
    std::vector<std::string> result;
    auto const& longestNodes = tree->findLongest();
    result.reserve(longestNodes.size());
    for(auto const& node : longestNodes)
        result.push_back(node->toString());
    return result;
}
