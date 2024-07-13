#include "GeneralsGameModel.h"
#include <random>

GeneralsGameModel::GeneralsGameModel() : gameStarted(false), surrendered(false) {}

std::shared_ptr<MapInfo> GeneralsGameModel::getMapInfo() throw() {
    return playerMap;
}

std::shared_ptr<MapInfo> GeneralsGameModel::getPlaybackMapInfo(int gameRound) throw() {
    return playbackMaps[gameRound];
}

int GeneralsGameModel::getPlayerNum() {
    return cntPlayer;
}

int GeneralsGameModel::getRound() {
    return round;
}

void GeneralsGameModel::initPlayers(int playerNum) {
    cntPlayer = playerNum;
    playerInfos.resize(playerNum);
    playerInfos[0] = std::make_shared<PlayerInfo>(playerName, 0);
    for (int i = 1; i < cntPlayer; ++i) {
        playerInfos[i] = std::make_shared<PlayerInfo>("Bot " + QString::number(i), i);
    }
    rankList = std::make_shared<QVector<std::shared_ptr<PlayerInfo>>>(playerInfos);
    playerMap->capitalDistribution(cntPlayer);
    auto map = playerMap->getMap();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (map[i][j]->getType() == CAPITAL) {
                playerInfos[map[i][j]->getOwner()]->setCapital(Point(i, j));
            }
        }
    }
}

void GeneralsGameModel::endGame() {
    gameStarted = false;
    for (auto &player : playerInfos) {
        player->clearMoveList();
    }
}

QString GeneralsGameModel::getPlayerName() {
    return playerName;
}

std::shared_ptr<QVector<std::shared_ptr<PlayerInfo>>> GeneralsGameModel::getRankList() {
    for (auto &player : playerInfos) {
        player->setLandNum(0);
        player->setArmyNum(0);
    }
    auto map = playerMap->getMap();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (map[i][j]->getOwner() == -1) continue;
            auto player = playerInfos[map[i][j]->getOwner()];
            player->setLandNum(player->getLandNum() + 1);
            player->setArmyNum(player->getArmyNum() + map[i][j]->getArmy());
        }
    }
    std::sort(rankList->begin(), rankList->end(), [](std::shared_ptr<PlayerInfo> a, std::shared_ptr<PlayerInfo> b) {
        return a->getArmyNum() > b->getArmyNum() || (a->getArmyNum() == b->getArmyNum() && a->getLandNum() > b->getLandNum());
    });
    return rankList;
}

void GeneralsGameModel::setPlayerName(const QString &nickname) {
    playerName = nickname;
}

void GeneralsGameModel::startGame(int playerNum, bool mode) {
    if (gameStarted) return;
    round = 0;
    gameMode = mode;

    playerMap = std::make_shared<MapInfo>();
    playerMap->generateRandomMap(100, 100);
    width = playerMap->getWidth();
    height = playerMap->getHeight();

    initPlayers(playerNum);
    surrendered = false;
    gameStarted = true;

    playbackMaps.clear();
    playbackMaps.push_back(std::make_shared<MapInfo>(*playerMap));
}

void GeneralsGameModel::startGame(int playerNum, bool mode, std::shared_ptr<MapInfo> map) {
    if (gameStarted) return;
    round = 0;
    gameMode = mode;

    playerMap = map;
    width = playerMap->getWidth();
    height = playerMap->getHeight();
    playerMap->initMap();

    initPlayers(playerNum);
    surrendered = false;
    gameStarted = true;

    playbackMaps.clear();
    playbackMaps.push_back(std::make_shared<MapInfo>(*playerMap));
}

bool GeneralsGameModel::move(int playerID, int x, int y, Direction dir, bool half) {
    int x_ = x + directions[dir].first, y_ = y + directions[dir].second;
    if (x_ < 0 || x_ >= height || y_ < 0 || y_ >= width || playerMap->getCell(x_, y_)->getType() == MOUNTAIN) return false;
    playerInfos[playerID]->addMove(x, y, dir, half);
    return true;
}

void GeneralsGameModel::addRound() {
    if (round % 50 == 0 && round != 0) {
        playerMap->increaseBlankArmy();
    } else if (round % 2 == 0) {
        playerMap->increaseCityArmy();
    }
    round++;
    playbackMaps.push_back(std::make_shared<MapInfo>(*playerMap));
}

void GeneralsGameModel::execMove() {
    for (auto &player : playerInfos) {
        if (!player->isAlive()) continue;
        if (!player->hasMove()) {
            player->setSlientRound(player->getSlientRound() + 1);
            continue;
        } else {
            player->setSlientRound(0);
        }
        auto move = player->getFirstMove();
        int x = move.x, y = move.y;
        int x_ = x + directions[move.dir].first, y_ = y + directions[move.dir].second;
        if (!moveArmy(player->getPlayerId(), x, y, x_, y_, move.half)) {
            player->clearMoveList();
        }
    }
    if (!playerInfos[0]->isAlive()) {
        clearMove(0);
    }
}

void GeneralsGameModel::changeOwner(int owner, int new_owner) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (playerMap->getCell(i, j)->getOwner() == owner) {
                playerMap->getCell(i, j)->setOwner(new_owner);
            }
        }
    }
}

bool GeneralsGameModel::moveArmy(int playerId, int x1, int y1, int x2, int y2, int mode) {
    auto map = playerMap->getMap();

    if (map[x1][y1]->getOwner() != playerId) {
        return false;
    }

    int army = map[x1][y1]->getArmy();
    army = (mode == 0) ? army - 1 : army / 2;

    if (map[x2][y2]->getOwner() == playerId) {
        map[x2][y2]->addArmy(army);
        map[x1][y1]->addArmy(-army);
    } else {
        int army2 = map[x2][y2]->getArmy();
        if (army > army2) {
            map[x2][y2]->setArmy(army - army2);
            if (map[x2][y2]->getType() == CAPITAL) {
                playerInfos[map[x2][y2]->getOwner()]->setLose(round);
                emit(playerInfos[map[x2][y2]->getOwner()]->getNickName());
                changeOwner(map[x2][y2]->getOwner(), playerId);
                if (gameMode) {
                    map[x2][y2]->setType(CAPITAL);
                    Point capital = playerInfos[playerId]->getCapital();
                    map[capital.first][capital.second]->setType(CITY);
                    playerInfos[playerId]->setCapital(Point(x2, y2));
                } else {
                    map[x2][y2]->setType(CITY);
                }
            } else {
                map[x2][y2]->setOwner(playerId);
            }
        } else {
            map[x2][y2]->addArmy(-army);
        }
        map[x1][y1]->addArmy(-army);
    }

    return true;
}

void GeneralsGameModel::clearMove(int playerID) {
    playerInfos[playerID]->clearMoveList();
}

void GeneralsGameModel::cancelMove(int playerID) {
    playerInfos[playerID]->cancelMove();
}

void GeneralsGameModel::surrender(int playerID) {
    playerInfos[playerID]->setLose(round);
    /*if (playerID == 0) {
        surrendered = true;
        endGame();
    }*/
    auto map = playerMap->getMap();
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (map[i][j]->getOwner() == playerID) {
                map[i][j]->setOwner(-1);
                if (map[i][j]->getType() == CellType::BLANK) map[i][j]->setArmy(0);
                    else map[i][j]->setType(CellType::CITY);
            }
}

void GeneralsGameModel::updateView() {
    auto map = playerMap->getMap();
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j]->getOwner() == 0) {
                map[i][j]->setLighted(true);
            } else {
                map[i][j]->setLighted(false);
                for (int k = 0; k < 8; k++) {
                    int x = i + dx[k], y = j + dy[k];
                    if (x < 0 || x >= height || y < 0 || y >= width) continue;
                    if (map[x][y]->getOwner() == 0) {
                        map[i][j]->setLighted(true);
                        break;
                    }
                }
            }
        }
    }
}

void GeneralsGameModel::addBotMove() {
    srand(time(nullptr));
    for (int i = 1; i < cntPlayer; i++) {
        if (!playerInfos[i]->isAlive() || playerInfos[i]->hasMove()) continue;
        if (movePriority(i)) continue;
        if (rand() % 3 == 0) {
            if (!moveToward(i)) {
                moveOutward(i);
            }
        } else {
            moveOutward(i);
        }
    }
}

bool GeneralsGameModel::movePriority(int playerID) {
    std::random_device rd;
    std::mt19937 gen(rd());

    QVector<int> cellPos;
    for (int i = 0; i < height * width; i++) {
        cellPos.push_back(i);
    }
    std::shuffle(cellPos.begin(), cellPos.end(), gen);

    auto map = playerMap->getMap();
    for (auto& pos : cellPos) {
        int i = pos / width, j = pos % width;
        if (map[i][j]->getOwner() == playerID || map[i][j]->getOwner() == -1) continue;
        for (int k = 0; k < 4; k++) {
            int x = i + directions[k].first, y = j + directions[k].second;
            if (x < 0 || x >= height || y < 0 || y >= width || map[x][y]->getOwner() != playerID) continue;
            if (map[x][y]->getArmy() <= map[i][j]->getArmy() + 1) continue;
            playerInfos[playerID]->addMove(x, y, (Direction)(k ^ 1), 0);
            return true;
        }
    }

    return false;
}

void GeneralsGameModel::moveOutward(int playerID) {
    std::random_device rd;
    std::mt19937 gen(rd());

    QVector<int> cellPos;
    for (int i = 0; i < height * width; i++) {
        cellPos.push_back(i);
    }
    std::shuffle(cellPos.begin(), cellPos.end(), gen);

    auto map = playerMap->getMap();
    for (auto& pos : cellPos) {
        int i = pos / width, j = pos % width;
        if (map[i][j]->getOwner() != playerID) continue;
        for (int k = 0; k < 4; k++) {
            int x = i + directions[k].first, y = j + directions[k].second;
            if (x < 0 || x >= height || y < 0 || y >= width || map[x][y]->getOwner() != -1 || map[x][y]->getType() == MOUNTAIN) continue;
            if (map[i][j]->getArmy() <= map[x][y]->getArmy() + 1) continue;
            playerInfos[playerID]->addMove(i, j, (Direction)k, 0);
            return;
        }
    }
}

static int getDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}
bool GeneralsGameModel::moveToward(int playerID) {
    auto map = playerMap->getMap();

    int x1 = -1, y1 = -1, x2 = -1, y2 = -1;
    int maxArmy = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j]->getOwner() != playerID) continue;
            if (map[i][j]->getArmy() > maxArmy) {
                maxArmy = map[i][j]->getArmy();
                x1 = i, y1 = j;
            }
        }
    }

    double minDist = height * width;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j]->getOwner() == playerID || map[i][j]->getType() == MOUNTAIN) continue;
            if (map[i][j]->getArmy() > 4 * maxArmy) continue;


            double dist = getDistance(x1, y1, i, j);
            if (map[i][j]->getType() == CAPITAL) {
                dist = dist * 0.9;
            } else if (map[i][j]->getType() == CITY) {
                if (map[i][j]->getOwner() != -1) {
                    dist = dist * std::max(1.2, std::min(map[i][j]->getArmy() / (3.2 * maxArmy), 20.0));
                } else {
                    dist = dist * 1.6;
                }
            } else if (map[i][j]->getType() == BLANK && map[i][j]->getOwner() == -1) {
                dist = dist * 2.5;
            }
            if (map[i][j]->getArmy() > maxArmy) {
                dist = dist * (1.6 * map[i][j]->getArmy() / maxArmy);
            }

            if (dist < minDist) {
                minDist = dist;
                x2 = i, y2 = j;
            }
        }
    }

    if (x1 == -1 || x2 == -1) return false;
    return findMoveWay(playerID, x1, y1, x2, y2);
}

bool GeneralsGameModel::findMoveWay(int playerID, int x1, int y1, int x2, int y2) {
    auto map = playerMap->getMap();

    int start = x1 * width + y1, end = x2 * width + y2;
    QVector<int> preDir(height * width, -1);

    QQueue<int> q;
    q.push_back(end);

    while (!q.empty()) {
        int pos = q.front();
        q.pop_front();
        int x = pos / width, y = pos % width;
        if (pos == start) break;

        for (int k = 0; k < 4; k++) {
            int x_ = x + directions[k].first, y_ = y + directions[k].second;
            if (x_ < 0 || x_ >= height || y_ < 0 || y_ >= width || (map[x_][y_]->getOwner() != playerID && (map[x_][y_]->getType() == CITY || map[x_][y_]->getType() == CAPITAL)) || map[x_][y_]->getType() == MOUNTAIN) continue;
            if (preDir[x_ * width + y_] == -1) {
                preDir[x_ * width + y_] = k ^ 1;
                q.push_back(x_ * width + y_);
            }
        }
    }

    if (preDir[start] == -1) return false;

    int pos = start;
    while (pos != end) {
        int x = pos / width, y = pos % width;
        playerInfos[playerID]->addMove(x, y, (Direction)preDir[pos], 0);
        x += directions[preDir[pos]].first;
        y += directions[preDir[pos]].second;
        pos = x * width + y;
    }
    return true;
}

void GeneralsGameModel::updateArrow() {
    auto map = playerMap->getMap();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            map[i][j]->setDirection(-1);
        }
    }

    auto moveList = playerInfos[0]->getMoveList();
    while (!moveList.empty()) {
        auto move = moveList.front();
        moveList.pop_front();
        int x = move.x, y = move.y;
        if (map[x][y]->getDirection() == -1) {
            map[x][y]->setDirection(move.dir);
        }
    }
}
