#pragma once
#include <iostream>
#include <string>

class Logger {
    inline static void show(const std::string& msg) {
        std::cout << msg << "\n";
    }
public:
    inline static void error(const std::string& msg) {
        show("ERR: " + msg);
    }

    inline static void info(const std::string& msg) {
        show("INF: " + msg);
    }

    inline static void debug(const std::string& msg) {
        show("DBG: " + msg);
    }

    inline static void warning(const std::string& msg) {
        show("WRN: " + msg);
    }
};
