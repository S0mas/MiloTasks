#include "gameengine.h"
#include <QCoreApplication>

unsigned GameEngine::positionToColumn(const unsigned position) const noexcept {
    return position%boardSideSize;
}

unsigned GameEngine::positionToRow(const unsigned position) const noexcept {
    return position/boardSideSize;
}
unsigned GameEngine::columnAndRowToPosition(const unsigned column, const unsigned row) const noexcept {
    return column + row*boardSideSize;
}

SignType GameEngine::getOpositPlayer(const SignType player) const noexcept {
    return player == SignType::Cross ? SignType::Nought : SignType::Cross;
}

bool GameEngine::isBoardFull() const noexcept {
    return moves.size() == 9;
}

void GameEngine::swapActivePlayer() noexcept {
    activePlayer = activePlayer == SignType::Cross ? SignType::Nought : SignType::Cross;
    emit playerChanged(activePlayer);
}

void GameEngine::checkGameStatus() noexcept {
        for(auto const& element : columnsRowsOrDiagonals)
            if(board[element[0]].sign == activePlayer && board[element[1]].sign == activePlayer && board[element[2]].sign == activePlayer){
                emit gameEnded(activePlayer, element);
                gameInProgress = false;
            }
    //draw
    if(isBoardFull()){
        emit gameEnded(SignType::Empty, {});
        gameInProgress = false;
    }
}

GameEngine::GameEngine(QObject *parent) : QObject(parent), activePlayer(SignType::Cross) {}

void GameEngine::newGame() {
   reset();
   swapActivePlayer();
   gameInProgress = true;
}

void GameEngine::move(const unsigned column, const unsigned row, SignType sign) {
    if(gameInProgress) {
        auto position = columnAndRowToPosition(column, row);
        if(sign == activePlayer && board[position].sign == SignType::Empty){
            board[position].sign = sign;
            emit updateSquare(column, row, sign);
            checkGameStatus();
            swapActivePlayer();
            QCoreApplication::processEvents();
            if(aiStatus[activePlayer])
                moveAI();
        }
        else
            emit badMove();
    }
}

void GameEngine::reset() {
    while(!moves.empty())
        undo();
}

void GameEngine::undo() {
    if(!moves.empty()){
        const auto square = moves.top();
        moves.pop();
        swapActivePlayer();
        emit updateSquare(square%3, square/3, SignType::Empty);
    }
}

void GameEngine::toggleAi(const SignType sign) {
    aiStatus[sign] = !aiStatus[sign];
}

std::optional<unsigned> GameEngine::findWinningMove(const SignType player) const noexcept {
    for(auto const& element : columnsRowsOrDiagonals){
        unsigned playerSignsCounter = 0;
        unsigned emptyCounter = 0;
        unsigned candidate;
        for(auto const& position : element){
            if(board[position].sign == player)
                ++playerSignsCounter;
            else if(board[position].sign == SignType::Empty){
                candidate = position;
                ++emptyCounter;
            }
        }
        if(playerSignsCounter == 2 && emptyCounter == 1)
            return candidate;
    }
    return {};
}

unsigned GameEngine::findBestMove() const noexcept {
    unsigned maxSignCounter = 0;
    unsigned bestMove = 0;
    for(auto i = 0u; i < board.size(); ++i){
        if(board[i].sign == SignType::Empty) {
            auto boardCopy = board;
            boardCopy[i].sign = activePlayer;
            unsigned signCounter = 0;
            for(auto const& element : columnsRowsOrDiagonals) {
                for(auto const& position : element) {
                    if(boardCopy[position].sign == activePlayer){
                        ++signCounter;
                        break;
                    }
                }
            }
            if(signCounter > maxSignCounter){
                maxSignCounter = signCounter;
                bestMove = i;
            }
        }
    }
    return bestMove;
}

void GameEngine::moveAI() noexcept {
    if(auto position = findWinningMove(activePlayer))
        move(*position%boardSideSize, *position/boardSideSize, activePlayer);
    else if(auto position = findWinningMove(getOpositPlayer(activePlayer)))
        move(*position%boardSideSize, *position/boardSideSize, activePlayer);
    else {
        auto bestMove = findBestMove();
        move(positionToColumn(bestMove), positionToRow(bestMove), activePlayer);
    }
}
