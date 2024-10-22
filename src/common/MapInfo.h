#pragma once

#include <QVector>
#include <QString>
#include <QDebug>
#include <QObject>

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
    bool isLighted_;
    int direction_;
public:
    Cell() : type_(BLANK), owner_(-1), army_(0), isLighted_(false), direction_(-1) {}
    Cell(CellType type, int owner, int army) : type_(type), owner_(owner), army_(army), isLighted_(false), direction_(-1) {}
    Cell(const Cell& other) : type_(other.type_), owner_(other.owner_), army_(other.army_), isLighted_(false), direction_(-1) {}

    CellType getType();
    int getOwner();
    int getArmy();
    bool isLighted();
    int getDirection();
    void setType(CellType type);
    void setOwner(int owner);
    void setArmy(int army);
    void addArmy(int army);
    void setLighted(bool isLighted);
    void setDirection(int direction);
};

class MapInfo : public QObject {
    Q_OBJECT

private:
    QVector<QVector<Cell*>> map_;
    int width_;
    int height_;
public:
    MapInfo();
    MapInfo(int width, int height)
        : width_(width), height_(height) {
        map_.resize(height);
        for (int i = 0; i < height; i++) {
            map_[i].resize(width);
            for (int j = 0; j < width; j++) {
                map_[i][j] = nullptr;
            }
        }
    }
    MapInfo(const MapInfo& other);

    ~MapInfo() {
        for (int i = 0; i < height_; i++) {
            for (int j = 0; j < width_; j++) {
                delete map_[i][j];
            }
        }
    }

    void generateRandomMap(int cityDense, int mountainDense);
    void capitalDistribution(int playerNum);
    void initMap();

    int getWidth();
    int getHeight();
    void setWidth(int width);
    void setHeight(int height);
    QVector<QVector<Cell*>> getMap();
    Cell* getCell(int x, int y);

    /**
     * @brief Increase the number of armies in the blank cell
     */
    void increaseBlankArmy();
    /**
     * @brief Increase the number of armies in the city and capital cell
     */
    void increaseCityArmy();
};
