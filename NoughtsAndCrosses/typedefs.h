#pragma once

enum class SignType {
    Nought,
    Cross,
    Empty
};

struct Square {
    unsigned column;
    unsigned row;
    SignType sign;
    constexpr Square(const unsigned column, const unsigned row) : column(column), row(row), sign(SignType::Empty) {}
};
