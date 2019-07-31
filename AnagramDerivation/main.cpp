#include "anagramderivationsolver.h"
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    std::string myword = "abe";
    auto alg = new AnagramDerivationSolver;

    const auto& start = std::chrono::high_resolution_clock::now();
    alg->createWordBaseFromFile("C:\\Users\\KrzysztofSommerfeld\\Documents\\MiloTasks\\AnagramDerivation\\words.txt");
    auto results = alg->solve(myword);
    const auto& stop = std::chrono::high_resolution_clock::now();

    for(auto const& result : results)
        std::cout << result << std::endl;


    std::cout << (stop - start).count() << std::endl;
    return 0;
}
