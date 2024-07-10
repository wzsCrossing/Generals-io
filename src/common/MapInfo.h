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
public:
    Cell() : type_(BLANK), owner_(-1), army_(0) {}
    Cell(CellType type, int owner, int army) : type_(type), owner_(owner), army_(army) {}

    CellType getType();
    int getOwner();
    int getArmy();
    void setType(CellType type);
    void setOwner(int owner);
    void setArmy(int army);
    void addArmy(int army);
};

class MapInfo : public QObject {
    Q_OBJECT

private:
    QVector<QVector<Cell*>> map_;
    int width_;
    int height_;
    int focus_x;
    int focus_y;
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
    ~MapInfo() {
        for (int i = 0; i < height_; i++) {
            for (int j = 0; j < width_; j++) {
                delete map_[i][j];
            }
        }
    }

    void importMap(const QString& fileName);
    void exportMap(const QString& fileName);
    void generateRandomMap(int cityDense, int mountainDense);
    void capitalDistribution(int playerNum);

    int getWidth();
    int getHeight();
    int getFocusX();
    int getFocusY();
    QVector<QVector<Cell*>> getMap();
    Cell* getCell(int x, int y);

    /**
     * @brief Move the army from (x1, y1) to (x2, y2)
     * @param mode 0: all, 1: half
     * @return true if the move is successful, false otherwise
     */
    bool moveArmy(int playerId, int x1, int y1, int x2, int y2, int mode);

    /**
     * @brief Increase the number of armies in the blank cell
     */
    void increaseBlankArmy();
    /**
     * @brief Increase the number of armies in the city and capital cell
     */
    void increaseCityArmy();
};
