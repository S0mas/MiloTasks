#include "anagramderivationsolver.h"
#include "anagramderivativenode.h"
#include "logger.h"
#include <sstream>
#include <string>
#include <chrono>
#include <thread>

std::vector<std::string> getUserInputTokens() {
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> tokens;
    std::istringstream tokenStream(input);
    std::string token;
    while (std::getline(tokenStream, token, ' '))
        tokens.push_back(token);
    return tokens;

}

void showAppInfo() {
    Logger::info("Options:");
    Logger::info("load <dictioneryFilepath>");
    Logger::info("solve <word> <dictioneryFilepath>");
    Logger::info("solve <word> (if dictionery is already loaded)");
    Logger::info("exit");
    Logger::info("You can also provide dictionery file as application start parameter");
}

void invalidInput() {
   Logger::error("Invalid Option selected.\n");
   showAppInfo();
}

int main(int argc, char *argv[]) {
    AnagramDerivationSolver alg;
    if(argc == 2)
        alg.createWordBaseFromFile(argv[1]);

    std::string userWord;
    showAppInfo();
    while(true){
        auto const& tokens = getUserInputTokens();
        if(tokens.size() == 1) {
            if(tokens[0] == "exit")
                break;
        }
        else if(tokens.size() == 2 || tokens.size() == 3) {
            if(tokens[0] == "solve"){
                if(tokens.size() == 3)
                    alg.createWordBaseFromFile(tokens.back());
                const auto& results = alg.solve(tokens[1]);
                for(auto const& result : results)
                    std::cout << result << std::endl;;
                Logger::info("Founded " + std::to_string(results.size()) +" results");
                Logger::info("Choose next option:");
                continue;
            }
            if(tokens[0] == "load" && tokens.size() == 2){
                alg.createWordBaseFromFile(tokens[1]);
                continue;
            }
        }
        invalidInput();
    }
    return 0;
}
