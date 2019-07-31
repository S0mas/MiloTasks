#include "anagramderivativenode.h"
#include "anagramderivationsolver.h"
#include "dictionaryparser.h"
#include "logger.h"

std::set<std::string> &AnagramDerivationSolver::findAnagrams(const std::string &word) {
    return anagramsBase.getAnagrams(word);
}

void AnagramDerivationSolver::createDerivedAnagrams(AnagramDerivativeNode *node) {
    for(auto const& letter : DictionaryParser::supportedLetters())
        node->addAnagramDerivatives(letter, findAnagrams(node->baseWord+letter));
}

bool AnagramDerivationSolver::findAnagramDerivationTreeHelper(std::stack<AnagramDerivativeNode *> &nodesStack) {
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

AnagramDerivativeNode *AnagramDerivationSolver::findAnagramDerivationTree(const std::string& base) {
    auto anagramTreeRoot = new AnagramDerivativeNode(base);
    std::stack<AnagramDerivativeNode*> toCalculate;
    toCalculate.push(anagramTreeRoot);
    while(findAnagramDerivationTreeHelper(toCalculate)){}
    return anagramTreeRoot;
}

void AnagramDerivationSolver::createWordBaseFromFile(const std::string &fileName, const unsigned aproxlinesNo) {
    AnagramStringHash::warnedAboutPerformance = false;
    anagramsBase.refill(fileName, aproxlinesNo);
}

std::vector<std::string> AnagramDerivationSolver::solve(std::string base) {
    DictionaryParser::tolower(base);
    if(auto c = DictionaryParser::isStrUsingInvalidChar(base)) {
        Logger::error("Base anagram " +  base + " contains unsupported character: " + *c);
        return {};
    }
    auto tree = findAnagramDerivationTree(base);
    std::vector<std::string> result;
    auto const& longestNodes = tree->findLongest();
    result.reserve(longestNodes.size());
    for(auto const& node : tree->findLongest())
        result.push_back(node->toString());
    return result;
}
