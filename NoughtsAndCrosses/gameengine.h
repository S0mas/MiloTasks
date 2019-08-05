#pragma once
#include "myarray.h"
#include "typedefs.h"
#include <optional>
#include <array>
#include <stack>
#include <QObject>
#include <vector>

class GameEngine : public QObject {
    Q_OBJECT
    static constexpr unsigned boardSideSize = 3;
    using ColumnRowDiagonal = std::array<unsigned, boardSideSize>;
    /*
     * 0 1 2
     * 3 4 5
     * 6 7 8
    */
    constexpr static std::array<ColumnRowDiagonal, 8> columnsRowsOrDiagonals = {
        ColumnRowDiagonal({0, 1, 2}), ColumnRowDiagonal({3, 4, 5}), ColumnRowDiagonal({6, 7, 8}),
        ColumnRowDiagonal({0, 3, 6}), ColumnRowDiagonal({1, 4, 7}), ColumnRowDiagonal({2, 5, 8}),
        ColumnRowDiagonal({0, 4, 8}), ColumnRowDiagonal({2, 4, 6})};
    std::array<Square, 9> board = {
        Square(0,0), Square(1,0), Square(2,0),
        Square(0,1), Square(1,1), Square(2,1),
        Square(0,2), Square(1,2), Square(2,2)};
    std::stack<unsigned, myArray<unsigned, 9>> moves;
    MyEnums::PlayerType activePlayer;
    std::map<MyEnums::PlayerType, bool> aiStatus;
    bool gameInProgress;

    bool isBoardFull() const noexcept;
    void checkGameStatus() noexcept;
    void swapActivePlayer() noexcept;
    MyEnums::PlayerType getOpositPlayer(const MyEnums::PlayerType player) const noexcept;
    void moveAI() noexcept;
    std::optional<unsigned> findWinningMove(const MyEnums::PlayerType player) const noexcept;
    unsigned findBestMove() const noexcept;
public:
    explicit GameEngine(QObject *parent = nullptr);
signals:
    void gameEnded(const unsigned player, const unsigned startIndex, const unsigned stopIndex);
    void playerChanged(const unsigned player);
    void badMove();
    void updateSquare(const unsigned index, const unsigned player);
    void toggleAiSig(const bool isOn, const unsigned player);
public slots:
    Q_INVOKABLE void newGame();
    Q_INVOKABLE void move(const unsigned index, const unsigned sign);
    Q_INVOKABLE void reset();
    Q_INVOKABLE void undo();
    Q_INVOKABLE void toggleAi(const unsigned player);
};
