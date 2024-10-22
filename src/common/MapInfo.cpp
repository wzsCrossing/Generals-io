#include "MapInfo.h"

#include <random>
#include <QQueue>

CellType Cell::getType() {
    return type_;
}

int Cell::getOwner() {
    return owner_;
}

int Cell::getArmy() {
    return army_;
}

bool Cell::isLighted() {
    return isLighted_;
}

int Cell::getDirection() {
    return direction_;
}

void Cell::setType(CellType type) {
    type_ = type;
}

void Cell::setOwner(int owner) {
    owner_ = owner;
}

void Cell::setArmy(int army) {
    army_ = army;
}

void Cell::addArmy(int army) {
    army_ += army;
}

void Cell::setLighted(bool isLighted) {
    isLighted_ = isLighted;
}

void Cell::setDirection(int direction) {
    direction_ = direction;
}

MapInfo::MapInfo() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rnd(16, 25);

    height_ = width_ = rnd(gen);
    map_.resize(height_);
    for (int i = 0; i < height_; i++) {
        map_[i].resize(width_);
        for (int j = 0; j < width_; j++) {
            map_[i][j] = nullptr;
        }
    }
}

MapInfo::MapInfo(const MapInfo& other) {
    width_ = other.width_;
    height_ = other.height_;

    map_.resize(height_);
    for (int i = 0; i < height_; i++) {
        map_[i].resize(width_);
        for (int j = 0; j < width_; j++) {
            map_[i][j] = new Cell(*(other.map_[i][j]));
        }
    }
}

static bool checkConnectivity(QVector<QVector<CellType>>& map, int width, int height) {
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    int blankNum = 0;
    QVector<QVector<bool>> visited(height);
    QQueue<QPair<int, int>> q;
    for (int i = 0; i < height; i++) {
        visited[i].resize(width);
        for (int j = 0; j < width; j++) {
            visited[i][j] = false;
            if (map[i][j] == BLANK) {
                blankNum++;
                if (q.empty()) {
                    q.push_back({i, j});
                    visited[i][j] = true;
                }
            }
        }
    }

    int count = 0;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop_front();
        count++;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < height && ny >= 0 && ny < width && !visited[nx][ny] && map[nx][ny] == BLANK) {
                q.push_back({nx, ny});
                visited[nx][ny] = true;
            }
        }
    }

    return count == blankNum;
}
void MapInfo::generateRandomMap(int cityDense, int mountainDense) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rnd(20, 35);

    QVector<QVector<CellType>> map(height_);
    for (int i = 0; i < height_; i++) {
        map[i].resize(width_);
        for (int j = 0; j < width_; j++) {
            map[i][j] = BLANK;
        }
    }

    QVector<int> cellPos;
    for (int i = 0; i < height_ * width_; i++) {
        cellPos.push_back(i);
    }
    std::shuffle(cellPos.begin(), cellPos.end(), gen);

    double dm = mountainDense / 255.0, dc = cityDense / 255.0;
    int pm = dm * width_ * height_ / 3, pc = dc * pm / 2;

    int count = 0;
    for (auto& pos : cellPos) {
        int x = pos / width_, y = pos % width_;
        map[x][y] = MOUNTAIN;

        if (count < pm && checkConnectivity(map, width_, height_)) {
            count++;
            if (count <= pc) {
                map[x][y] = CITY;
            } else if (count == pm) {
                break;
            }
        } else {
            map[x][y] = BLANK;
        }
    }

    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < width_; j++) {
            if (map[i][j] == MOUNTAIN) {
                map_[i][j] = new Cell(MOUNTAIN, -1, 0);
            } else if (map[i][j] == CITY) {
                map_[i][j] = new Cell(CITY, -1, rnd(gen));
            } else {
                map_[i][j] = new Cell();
            }
        }
    }
}

static int getDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}
void MapInfo::capitalDistribution(int playerNum) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rnd(0, height_ * width_ - 1);

    QVector<QVector<int>> capitalPos(playerNum);
    for (int i = 0; i < playerNum; i++) {
        capitalPos[i].resize(2);
    }

    for (int i = 0; i < playerNum; i++) {
        while (true) {
            int pos = rnd(gen);
            int x = pos / width_, y = pos % width_;
            if (map_[x][y]->getType() != BLANK) {
                continue;
            }

            bool flag = true;
            for (int j = 0; j < i; j++) {
                if (getDistance(x, y, capitalPos[j][0], capitalPos[j][1]) < 5) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                capitalPos[i][0] = x;
                capitalPos[i][1] = y;
                break;
            }
        }
    }

    for (int i = 0; i < playerNum; i++) {
        map_[capitalPos[i][0]][capitalPos[i][1]]->setType(CAPITAL);
        map_[capitalPos[i][0]][capitalPos[i][1]]->setOwner(i);
        map_[capitalPos[i][0]][capitalPos[i][1]]->setArmy(1);
    }
}

int MapInfo::getWidth() {
    return width_;
}

int MapInfo::getHeight() {
    return height_;
}

void MapInfo::setWidth(int width) {
    width_ = width;
}

void MapInfo::setHeight(int height) {
    height_ = height;
}

QVector<QVector<Cell*>> MapInfo::getMap() {
    return map_;
}

Cell* MapInfo::getCell(int x, int y) {
    return map_[x][y];
}

void MapInfo::increaseBlankArmy() {
    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < width_; j++) {
            if (map_[i][j]->getType() == BLANK && map_[i][j]->getOwner() != -1) {
                map_[i][j]->addArmy(1);
            }
        }
    }
}

void MapInfo::increaseCityArmy() {
    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < width_; j++) {
            if ((map_[i][j]->getType() == CITY && map_[i][j]->getOwner() != -1) || map_[i][j]->getType() == CAPITAL) {
                map_[i][j]->addArmy(1);
            }
        }
    }
}

void MapInfo::initMap() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rnd(20, 35);

    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            if (map_[i][j]->getType() == CITY) {
                map_[i][j]->setArmy(rnd(gen));
            }
        }
    }
}
