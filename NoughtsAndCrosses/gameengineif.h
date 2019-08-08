#pragma once
#include "gameengine.h"

#include <QObject>
#include <QThread>

class GameEngineIF : public QObject {
    Q_OBJECT
    QThread gameEngineThread;
    GameEngine gameEngine;
public:
    explicit GameEngineIF(QObject *parent = nullptr);
    ~GameEngineIF() override;
signals:
    void newGameSig();
    void moveSig(const unsigned index, const unsigned sign);
    void resetSig();
    void undoSig();
    void toggleAiSig(const unsigned player);

    void gameEndedSig(const unsigned player, const std::vector<int>& squares);
    void playerChangedSig(const unsigned player);
    void badMoveSig();
    void updateSquareSig(const unsigned index, const unsigned player);
    void toggleAiResponseSig(const bool isOn, const unsigned player);
public slots:
    void newGame();
    void move(const unsigned index, const unsigned sign);
    void reset();
    void undo();
    void toggleAi(const unsigned player);

    void gameEnded(const unsigned player, const std::vector<int>& squares);
    void playerChanged(const unsigned player);
    void badMove();
    void updateSquare(const unsigned index, const unsigned player);
    void toggleAiResponse(const bool isOn, const unsigned player);
};
