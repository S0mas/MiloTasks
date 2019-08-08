#pragma once
#include "myarray.h"
#include "typedefs.h"

#include <optional>
#include <stack>
#include <vector>

#include <QObject>

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
    void gameEnded(const unsigned player, const std::vector<int>& squares);
    void playerChanged(const unsigned player);
    void badMove();
    void updateSquare(const unsigned index, const unsigned player);
    void toggleAiSig(const bool isOn, const unsigned player);
public slots:
    void newGame();
    void move(const unsigned index, const unsigned sign);
    void reset();
    void undo();
    void toggleAi(const unsigned player);
    void process();
};
