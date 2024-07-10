#pragma once

#include <QString>
#include <QQueue>

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Move {
    int x, y;
    Direction dir;
    bool half;
    Move() = default;
    Move(int _x, int _y, Direction _dir, bool _half)
        : x(_x), y(_y), dir(_dir), half(_half) {}
};

class PlayerInfo {
private:
    QString nickName_;
    int playerId_;
    int landNum_;
    int armyNum_;
    bool isReady_;
    bool isAlive_;
    int silentRound_;
    QQueue<Move> moveList_;
public:
    PlayerInfo(const QString& nickName, int playerId)
        : nickName_(nickName), playerId_(playerId), isReady_(false), isAlive_(true), silentRound_(0) {}

    QString getNickName();
    int getLandNum();
    int getArmyNum();
    int getPlayerId();
    bool isReady();
    bool isAlive();
    int getSlientRound();
    void setLandNum(int landNum);
    void setArmyNum(int armyNum);
    void setReady(bool isReady);
    void setAlive(bool isAlive);
    void setSlientRound(int silentRound);

    void addMove(int x, int y, Direction dir, bool half);
    Move getFirstMove();
    bool hasMove();
    void clearMoveList();
};
