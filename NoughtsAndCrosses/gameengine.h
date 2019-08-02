#pragma once
#include "myarray.h"
#include "typedefs.h"
#include <optional>
#include <stack>
#include <QObject>


class GameEngine : public QObject {
    Q_OBJECT
    static constexpr unsigned boardSideSize = 3;
    using ColumnRowDiagonal = std::array<unsigned, boardSideSize>;
    constexpr static std::array<ColumnRowDiagonal, 8> columnsRowsOrDiagonals = {
        ColumnRowDiagonal({0, 1, 2}), ColumnRowDiagonal({3, 4, 5}), ColumnRowDiagonal({5, 7, 8}),
        ColumnRowDiagonal({0, 3, 6}), ColumnRowDiagonal({1, 4, 7}), ColumnRowDiagonal({2, 5, 8}),
        ColumnRowDiagonal({0, 4, 8}), ColumnRowDiagonal({2, 4, 6})};
    std::array<Square, 9> board = {
        Square(0,0), Square(1,0), Square(2,0),
        Square(0,1), Square(1,1), Square(2,1),
        Square(0,2), Square(1,2), Square(2,2)};
    std::stack<unsigned, myArray<unsigned, 9>> moves;
    SignType activePlayer;
    std::map<SignType, bool> aiStatus;
    bool gameInProgress;

    bool isBoardFull() const noexcept;
    void checkGameStatus() noexcept;
    void swapActivePlayer() noexcept;
    SignType getOpositPlayer(const SignType player) const noexcept;
    void moveAI() noexcept;
    std::optional<unsigned> findWinningMove(const SignType player) const noexcept;
    unsigned findBestMove() const noexcept;
    unsigned positionToColumn(const unsigned position) const noexcept;
    unsigned positionToRow(const unsigned position) const noexcept;
    unsigned columnAndRowToPosition(const unsigned column, const unsigned row) const noexcept;
public:
    Q_ENUMS(SignType)
    explicit GameEngine(QObject *parent = nullptr);
signals:
    void gameEnded(SignType winner, ColumnRowDiagonal squares = {});
    void playerChanged(SignType player);
    void badMove();
    void updateSquare(const unsigned column, const unsigned row, SignType sign);
public slots:
    void newGame();
    void move(const unsigned column, const unsigned row, SignType sign);
    void reset();
    void undo();
    void toggleAi(const SignType sign);
};
