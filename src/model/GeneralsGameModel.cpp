#include "GeneralsGameModel.h"

GeneralsGameModel::GeneralsGameModel() : gameStarted(false), surrendered(false) {}

std::shared_ptr<MapInfo> GeneralsGameModel::getMapInfo() throw() {
    return playerMap;
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
    playerMap->capitalDistribution(cntPlayer);
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
    rankList = playerInfos;
    std::sort(rankList.begin(), rankList.end(), [](std::shared_ptr<PlayerInfo> a, std::shared_ptr<PlayerInfo> b) {
        return a->getArmyNum() > b->getArmyNum() || (a->getArmyNum() == b->getArmyNum() && a->getLandNum() > b->getLandNum());
    });
    return std::make_shared<QVector<std::shared_ptr<PlayerInfo>>>(rankList);
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
}

void GeneralsGameModel::startGame(int playerNum, bool mode, std::shared_ptr<MapInfo> map) {
    if (gameStarted) return;
    round = 0;
    gameMode = mode;

    playerMap = map;
    width = playerMap->getWidth();
    height = playerMap->getHeight();

    initPlayers(playerNum);
    surrendered = false;
    gameStarted = true;
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
    if (playerID == 0) {
        surrendered = true;
        endGame();
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
