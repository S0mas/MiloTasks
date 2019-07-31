#include "anagramderivationsolver.h"
#include <iostream>

#include <thread>

int main() {
    std::string myword = "abe";
    auto alg = new AnagramDerivationSolver;

    alg->createWordBaseFromFile("D:\\MiloTasks\\AnagramDerivation\\words.txt");
    auto results = alg->solve(myword);

    for(auto const& result : results)
        std::cout << result << std::endl;

    return 0;
}
