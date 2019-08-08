#include "gameengineif.h"

GameEngineIF::GameEngineIF(QObject *parent) : QObject(parent) {
    connect(this, SIGNAL(newGameSig()), &gameEngine, SLOT(newGame()));
    connect(this, SIGNAL(moveSig(const unsigned, const unsigned)), &gameEngine, SLOT(move(const unsigned, const unsigned)));
    connect(this, SIGNAL(resetSig()), &gameEngine, SLOT(reset()));
    connect(this, SIGNAL(undoSig()), &gameEngine, SLOT(undo()));
    connect(this, SIGNAL(toggleAiSig(const unsigned)), &gameEngine, SLOT(toggleAi(const unsigned)));

    connect(&gameEngine, SIGNAL(gameEnded(const unsigned, const std::vector<int>&)), this, SLOT(gameEnded(const unsigned, const std::vector<int>&)));
    connect(&gameEngine, SIGNAL(playerChanged(const unsigned)), this, SLOT(playerChanged(const unsigned)));
    connect(&gameEngine, SIGNAL(badMove()), this, SLOT(badMove()));
    connect(&gameEngine, SIGNAL(updateSquare(const unsigned, const unsigned)), this, SLOT(updateSquare(const unsigned, const unsigned)));
    connect(&gameEngine, SIGNAL(toggleAiSig(const bool, const unsigned)), this, SLOT(toggleAiResponse(const bool, const unsigned)));

    connect(&gameEngineThread, SIGNAL(started()), &gameEngine, SLOT(process()));
    gameEngine.moveToThread(&gameEngineThread);
    gameEngineThread.start();
}

GameEngineIF::~GameEngineIF() {
    gameEngineThread.requestInterruption();
    gameEngineThread.quit();
    gameEngineThread.wait(1000);
}

void GameEngineIF::newGame() {
    emit newGameSig();
}

void GameEngineIF::move(const unsigned index, const unsigned sign) {
    emit moveSig(index, sign);
}

void GameEngineIF::reset() {
    emit resetSig();
}

void GameEngineIF::undo() {
    emit undoSig();
}

void GameEngineIF::toggleAi(const unsigned player) {
    emit toggleAiSig(player);
}

void GameEngineIF::gameEnded(const unsigned player, const std::vector<int> &squares) {
    emit gameEndedSig(player, squares);
}

void GameEngineIF::playerChanged(const unsigned player) {
    emit playerChangedSig(player);
}

void GameEngineIF::badMove() {
    emit badMoveSig();
}

void GameEngineIF::updateSquare(const unsigned index, const unsigned player) {
    emit updateSquareSig(index, player);
}

void GameEngineIF::toggleAiResponse(const bool isOn, const unsigned player) {
    emit toggleAiResponseSig(isOn, player);
}
