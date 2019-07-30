#include <map>
#include <cctype>
#include <iostream>
#include "findanagram.h"

void showAnagram(const AnagramDerivative* anagram) {
   auto root = anagram;
   if(root->parent != nullptr){
       showAnagram(root->parent);
       std::cout <<" + " << AnagramStringHash::mapPrimeToLetter(AnagramStringHash::hash(root->base)/AnagramStringHash::hash(root->parent->base)) << " = ";
   }
   std::cout << root->base;
}

void findBiggestHelper(size_t& deepth, const AnagramDerivative* node, std::vector<AnagramDerivative*>& results) {
    for(auto const& map : node->biggerAnagrams) {
        for(auto const& el : map.second) {
            if(el->base.size() > deepth) {
                results.clear();
                deepth = el->base.size();
                results.push_back(el);
            }
            else if(el->base.size() == deepth)
                results.push_back(el);
            findBiggestHelper(deepth, el, results);
        }
    }
}

std::vector<AnagramDerivative*> findBiggest(const AnagramDerivative* root) {
   size_t deepth = 3;
   std::vector<AnagramDerivative*> results;
   findBiggestHelper(deepth, root, results);
   return results;
}

int main() {
    auto alg = new AnagramDerivationAlg;
    std::string myword = "noob";
    alg->createWordBaseFromFile("D:\\MiloTasks\\AnagramDerivation\\words.txt");
    std::cout << "wordBase created\n";
    const auto& anagramsDeriv = alg->findAnagramDerivation(myword);
    std::cout << "anagrams created\n";
    for(auto const& biggest : findBiggest(anagramsDeriv)){
        showAnagram(biggest);
        std::cout << "\n";
    }

    return 0;
}
