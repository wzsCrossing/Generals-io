#pragma once

#include "MapInfo.h"
#include <QVector>
#include <QString>

class UserInfo {
private:
    QString name_;
    int cityNum_;
    int armyNum_;
public:
    UserInfo(const QString& name, int cityNum, int armyNum)
        : name_(name), cityNum_(cityNum), armyNum_(armyNum) {}

    QString getName();
    int getCityNum();
    int getArmyNum();
    void setCityNum(int cityNum);
    void setArmyNum(int armyNum);
    void addCityNum(int cityNum);
    void addArmyNum(int armyNum);
};

class TeamInfo {
private:
    QVector<UserInfo*> users_;
public:
    TeamInfo() {}
    TeamInfo(QVector<UserInfo*> users) : users_(users) {}

    void addUser(UserInfo* user);
    void deleteUser(const QString& name);
    UserInfo getUser(const QString& name);
    QVector<UserInfo*> getUsers();
    int getUserNum();
    int getCityNum();
    int getArmyNum();
};

class GameInfo {
private:
    MapInfo* map_;
    int teamNum_;
    int playerNum_;
    QVector<UserInfo*> users_;
    QVector<TeamInfo*> teams_;
public:
    GameInfo(int width, int height, int teamNum, int playerNum)
        : map_(new MapInfo(width, height)), teamNum_(teamNum), playerNum_(playerNum) {}

    bool importGame(const QString& fileName);
    void exportGame(const QString& fileName);
    void randomGame(int cityDense, int mountainDense);
    void capitalDistribution();

    MapInfo getMap();
    UserInfo getUser(const QString& name);
    TeamInfo getTeam(int team);
    void addUser(const QString& name, int cityNum, int armyNum);
    void deleteUser(const QString& name);
    void addCity(const QString& name, int cityNum);
    void addArmy(const QString& name, int armyNum);
    void changeOwner(int x, int y, const QString& name);
    void changeType(int x, int y, CellType type);
    void moveArmy(int x1, int y1, int x2, int y2, int armyNum);
    void attack(int x1, int y1, int x2, int y2);
    void endTurn();
    void endGame();
};
