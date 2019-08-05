#pragma once
#include <QObject>

class MyEnums : public QObject {
    Q_OBJECT
public:
    enum class PlayerType {
        Nought,
        Cross,
        Empty
    };
};

struct Square {
    unsigned column;
    unsigned row;
    MyEnums::PlayerType sign;
    constexpr Square(const unsigned column, const unsigned row) : column(column), row(row), sign(MyEnums::PlayerType::Empty) {}
};
