#pragma once

#include "MapInfo.h"
#include "PlayerInfo.h"
#include <QVector>
#include <QString>

class GameInfo {
private:
    MapInfo* map_;
    int playerNum_;
    QVector<PlayerInfo*> players_;
public:
    GameInfo()
        : map_(new MapInfo()), playerNum_(0) {}
    ~GameInfo();

    void importGame(const QString& fileName, int width, int height);
    void exportGame(const QString& fileName);
    void generateRandomGame(int cityDense, int mountainDense);

    MapInfo* getMap();
    int getPlayerNum();
    PlayerInfo* getPlayer(int playerId);
    QVector<PlayerInfo*> getRankList();

    void addPlayer(const QString& nickName);
    void excuteMove();
    void addMove(int playerId, int x, int y, Direction dir, int mode);
};
