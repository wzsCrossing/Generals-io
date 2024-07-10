#ifndef GANERALS_GAME_MODEL_H
#define GANERALS_GAME_MODEL_H

#include <cmath>
#include <algorithm>
#include "MapInfo.h"
#include "GameInfo.h"

class GeneralsGameModel {
public:
    GeneralsGameModel();
    std::shared_ptr<MapInfo> getMapInfo() throw();
    int getPlayerNum();
    QVector<std::shared_ptr<PlayerInfo>> getRankList();
    void startGame(const QString &nickname);
    void setFocus(int x, int y);
    void move(int x, int y, Direction dir, bool half);
    void clearMove();
    void cancelMove();
    void surrender();
    void addRound();

private:
    void execMove();
    void generateRandomGame(int cityDense, int mountainDense, int playerNum);

    const std::pair<int, int> directions[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    bool gameStarted{}, surrendered{};
    int gameMode{}, cntPlayer{};
    int width, height, round;

    std::shared_ptr<Focus> focus{};
    QString playerName;
    std::shared_ptr<MapInfo> playerMap;
    QVector<std::shared_ptr<PlayerInfo>> playerInfos; // 0: player, 1 ~ cntPlayer - 1: bots
};

#endif // GANERALS_GAME_MODEL_H