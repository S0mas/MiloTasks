#include <map>
#include <cctype>
#include <iostream>
#include "findanagram.h"

void showAnagram(const AnagramDerivative* anagram) {
    for(auto const& el : anagram->biggerAnagrams)
        std::cout << el->base << ", ";

    std::cout << "\n  NEXT::::::LEVEL \n";
    if(!anagram->biggerAnagrams.empty())
        showAnagram(anagram->biggerAnagrams.back());
}



int main() {
    auto alg = new AnagramDerivationAlg;
    std::string myword = "lol";
    alg->createWordBaseFromFile("C:\\Users\\KrzysztofSommerfeld\\Documents\\MiloTasks\\AnagramDerivation\\words.txt");
    std::cout << "wordBase created\n";
    const auto& anagramsDeriv = alg->findAnagramDerivation(myword);
    std::cout << "anagrams created\n";
    showAnagram(anagramsDeriv);

    return 0;
}
