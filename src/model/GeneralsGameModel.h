#ifndef GANERALS_GAME_MODEL_H
#define GANERALS_GAME_MODEL_H

#include <cmath>
#include <algorithm>
#include "PlayerInfo.h"
#include "MapInfo.h"

class GeneralsGameModel {
public:
    GeneralsGameModel();
    std::shared_ptr<MapInfo> getMapInfo() throw();
    int getPlayerNum();
    QString getPlayerName();
    int getRound();
    std::shared_ptr<QVector<std::shared_ptr<PlayerInfo>>> getRankList();
    void setPlayerName(const QString &nickname);
    void startGame();
    void setFocus(int x, int y);
    bool move(int playerID, int x, int y, Direction dir, bool half);
    void changeOwner(int owner, int new_owner);
    bool moveArmy(int playerId, int x1, int y1, int x2, int y2, int mode);
    void clearMove();
    void cancelMove();
    void surrender();
    void addRound();
    void execMove();
    void updateView();

private:
    void generateRandomGame(int cityDense, int mountainDense, int playerNum);

    const std::pair<int, int> directions[4] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    bool gameStarted{}, surrendered{};
    int gameMode{}, cntPlayer{};
    int width, height, round;

    std::shared_ptr<Focus> focus{};
    QString playerName;
    std::shared_ptr<MapInfo> playerMap;
    QVector<std::shared_ptr<PlayerInfo>> playerInfos; // 0: player, 1 ~ cntPlayer - 1: bots
    QVector<std::shared_ptr<PlayerInfo>> rankList;
};

#endif // GANERALS_GAME_MODEL_H
