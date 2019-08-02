#pragma once
#include <array>
template<typename T, const unsigned SIZE>
class myArray : std::array<unsigned, SIZE> {
    unsigned counter = 0;
public:
    constexpr myArray(){}
    T& back() {
        return at(counter);
    }
    void push_back() {
        back(counter++);
    }
    void pop_back() {
        --counter;
    }
};
