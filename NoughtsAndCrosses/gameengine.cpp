#include "gameengine.h"
#include <QCoreApplication>
#include <QtGlobal>
#include <thread>
#include <chrono>

static MyEnums::PlayerType mapUnsignedToSignType(const unsigned player) {
    switch (player) {
    case 1:
        return MyEnums::PlayerType::Nought;
    case 2:
        return MyEnums::PlayerType::Cross;
    default:
        return MyEnums::PlayerType::Empty;
    }
}


static unsigned mapSignTypeToUnsigned(const MyEnums::PlayerType player) {
    switch (player) {
    case MyEnums::PlayerType::Nought:
        return 1;
    case MyEnums::PlayerType::Cross:
        return 2;
    default:
        return 0;
    }
}

MyEnums::PlayerType GameEngine::getOpositPlayer(const MyEnums::PlayerType player) const noexcept {
    return player == MyEnums::PlayerType::Cross ? MyEnums::PlayerType::Nought : MyEnums::PlayerType::Cross;
}

bool GameEngine::isBoardFull() const noexcept {
    return moves.size() == 9;
}

void GameEngine::swapActivePlayer() noexcept {
    activePlayer = getOpositPlayer(activePlayer);
    emit playerChanged(mapSignTypeToUnsigned(activePlayer));
}

void GameEngine::checkGameStatus() noexcept {
    for(auto const& element : columnsRowsOrDiagonals)
        if(board[element[0]].sign == activePlayer && board[element[1]].sign == activePlayer && board[element[2]].sign == activePlayer){
            emit gameEnded(mapSignTypeToUnsigned(activePlayer), element[0], element.back());
            gameInProgress = false;
            return;
        }
    //draw
    if(isBoardFull()){
        emit gameEnded(mapSignTypeToUnsigned(MyEnums::PlayerType::Empty), 0, 0);
        gameInProgress = false;
    }
}

GameEngine::GameEngine(QObject *parent) : QObject(parent), activePlayer(MyEnums::PlayerType::Cross) {}

void GameEngine::newGame() {
   QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents, 100);
   gameInProgress = true;
   reset();
   swapActivePlayer();
   if(aiStatus[activePlayer])
       moveAI();
}

void GameEngine::move(const unsigned index, const unsigned sign) {
    QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents, 100);
    if(gameInProgress) {
        auto signType = mapUnsignedToSignType(sign);
        if(signType == activePlayer && board[index].sign == MyEnums::PlayerType::Empty){
            board[index].sign = signType;
            moves.push(index);
            emit updateSquare(index, mapSignTypeToUnsigned(signType));
            checkGameStatus();
            swapActivePlayer();
            if(aiStatus[activePlayer] && gameInProgress){
                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                moveAI();
            }
        }
        else
            emit badMove();
    }
}

void GameEngine::reset() {
    QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents, 100);
    while(!moves.empty() && gameInProgress)
        undo();
}

void GameEngine::undo() {
    QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents, 100);
    if(!moves.empty() && gameInProgress){
        const auto index = moves.top();
        board[index].sign = MyEnums::PlayerType::Empty;
        moves.pop();
        swapActivePlayer();
        emit updateSquare(index, mapSignTypeToUnsigned(MyEnums::PlayerType::Empty));
    }
}

void GameEngine::toggleAi(const unsigned sign) {
    QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents, 100);
    aiStatus[mapUnsignedToSignType(sign)] = !aiStatus[mapUnsignedToSignType(sign)];
    emit toggleAiSig(aiStatus[mapUnsignedToSignType(sign)], sign);
    if(aiStatus[activePlayer])
        moveAI();
}

std::optional<unsigned> GameEngine::findWinningMove(const MyEnums::PlayerType player) const noexcept {
    std::vector<unsigned> candidates;
    for(auto const& element : columnsRowsOrDiagonals){
        unsigned playerSignsCounter = 0;
        unsigned emptyCounter = 0;
        unsigned candidate;
        for(auto const& position : element){
            if(board[position].sign == player)
                ++playerSignsCounter;
            else if(board[position].sign == MyEnums::PlayerType::Empty){
                candidate = position;
                ++emptyCounter;
            }
        }
        if(playerSignsCounter == 2 && emptyCounter == 1)
            candidates.push_back(candidate);
    }
    if(candidates.empty())
        return {};
    return candidates[qrand()%candidates.size()];
}

unsigned GameEngine::findBestMove() const noexcept {
    unsigned maxSignCounter = 0;
    std::vector<unsigned> bestMoves;
    for(auto i = 0u; i < board.size(); ++i){
        if(board[i].sign == MyEnums::PlayerType::Empty) {
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
                bestMoves.clear();
                maxSignCounter = signCounter;
                bestMoves.push_back(i);
            }
            else if(signCounter == maxSignCounter)
                bestMoves.push_back(i);
        }
    }
    if(gameInProgress)
        return bestMoves[qrand()%bestMoves.size()];
    else
        return 0;
}

void GameEngine::moveAI() noexcept {
    if(auto position = findWinningMove(activePlayer))
        move(*position, mapSignTypeToUnsigned(activePlayer));
    else if(auto position = findWinningMove(getOpositPlayer(activePlayer)))
        move(*position, mapSignTypeToUnsigned(activePlayer));
    else
        move(findBestMove(), mapSignTypeToUnsigned(activePlayer));
}

