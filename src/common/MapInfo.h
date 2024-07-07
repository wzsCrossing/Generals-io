#pragma once

#include <QVector>
#include <QString>

enum CellType {
    MOUNTAIN,
    CAPITAL,
    CITY,
    BLANK
};

class Cell {
private:
    CellType type_;
    int owner_;
    int army_;
public:
    Cell(CellType type, int owner, int army) : type_(type), owner_(owner), army_(army) {}

    CellType getType();
    int getOwner();
    int getArmy();
    void setType(CellType type);
    void setOwner(int owner);
    void setArmy(int army);
    void addArmy(int army);
};

class MapInfo {
private:
    QVector<QVector<Cell>> map_;
    int width_;
    int height_;
public:
    MapInfo(int width, int height)
        : width_(width), height_(height) {
        map_.resize(height);
        for (int i = 0; i < height; i++) {
            map_[i].resize(width);
        }
    }

    bool importMap(const QString& fileName);
    void exportMap(const QString& fileName);
    void randomMap(int cityDense, int mountainDense);
    void capitalDistribution(int playerNum);

    Cell getCell(int x, int y);
    void addArmy(int x, int y, int army);
    void changeOwner(int x, int y, int owner);
    void changeType(int x, int y, CellType type);
};
