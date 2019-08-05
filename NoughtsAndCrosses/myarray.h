#pragma once
#include <array>
#include <utility>

template<typename T, const unsigned SIZE>
class myArray : public std::array<unsigned, SIZE> {
    unsigned counter = 0;
public:
    constexpr myArray(){}
    T& back() {
        return at(counter-1);
    }

    void push_back(const T& element) {
        counter++;
        back() = element;
    }

    void push_back(T&& element) {
        back(++counter) = std::move(element);
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
