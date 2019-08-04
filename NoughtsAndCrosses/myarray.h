#pragma once
#include <array>
template<typename T, const unsigned SIZE>
class myArray : public std::array<unsigned, SIZE> {
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

    size_t size() const noexcept {
        return counter;
    }

    bool empty() const noexcept {
        return size() == 0;
    }
};
