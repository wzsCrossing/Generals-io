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
    std::shared_ptr<MapInfo> getPlaybackMapInfo(int gameRound) throw();
    int getPlayerNum();
    QString getPlayerName();
    int getRound();
    std::shared_ptr<QVector<std::shared_ptr<PlayerInfo>>> getRankList();
    void setPlayerName(const QString &nickname);
    void startGame(int playerNum, bool mode);
    void startGame(int playerNum, bool mode, std::shared_ptr<MapInfo> map);
    bool move(int playerID, int x, int y, Direction dir, bool half);
    void changeOwner(int owner, int new_owner);
    bool moveArmy(int playerID, int x1, int y1, int x2, int y2, int mode);
    void clearMove(int playerID);
    void cancelMove(int playerID);
    void surrender(int playerID);
    void addRound();
    void execMove();
    void updateView();
    void addBotMove();
    void updateArrow();
    void endGame();

private:
    void generateRandomGame(int cityDense, int mountainDense, int playerNum);
    bool movePriority(int playerID);
    void moveOutward(int playerID);
    bool moveToward(int playerID);
    bool findMoveWay(int playerID, int x1, int y1, int x2, int y2);
    void initPlayers(int playerNum);

    const std::pair<int, int> directions[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    bool gameStarted{}, surrendered{};
    bool gameMode{}; // true: leapfrog
    int cntPlayer{};
    int width, height, round;

    QString playerName;
    std::shared_ptr<MapInfo> playerMap;
    QVector<std::shared_ptr<MapInfo>> playbackMaps;
    QVector<std::shared_ptr<PlayerInfo>> playerInfos; // 0: player, 1 ~ cntPlayer - 1: bots
    std::shared_ptr<QVector<std::shared_ptr<PlayerInfo>>> rankList;
};

#endif // GANERALS_GAME_MODEL_H
