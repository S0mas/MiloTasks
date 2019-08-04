#pragma once
#include <QObject>

class MyEnums : public QObject {
    Q_OBJECT
public:
    enum class SignType {
        Nought,
        Cross,
        Empty
    };
};

struct Square {
    unsigned column;
    unsigned row;
    MyEnums::SignType sign;
    constexpr Square(const unsigned column, const unsigned row) : column(column), row(row), sign(MyEnums::SignType::Empty) {}
};
