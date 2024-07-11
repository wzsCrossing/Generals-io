#include "GeneralsGameModel.h"

GeneralsGameModel::GeneralsGameModel() :
    gameStarted(false), surrendered(false), gameMode(0), round(0) {
    playerMap = std::make_shared<MapInfo>();
}

std::shared_ptr<MapInfo> GeneralsGameModel::getMapInfo() throw() {
    return playerMap;
}

int GeneralsGameModel::getPlayerNum() {
    return cntPlayer;
}

int GeneralsGameModel::getRound() {
    return round;
}

void GeneralsGameModel::generateRandomGame(int cityDense, int mountainDense, int playerNum) {
    cntPlayer = playerNum;
    playerInfos.push_back(std::make_shared<PlayerInfo>(playerName, 0));
    for (int i = 1; i < cntPlayer; ++i) {
        playerInfos.push_back(std::make_shared<PlayerInfo>("Bot " + QString::number(i), i));
    }
    playerMap->generateRandomMap(cityDense, mountainDense);
    playerMap->capitalDistribution(cntPlayer);
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
    QVector<std::shared_ptr<PlayerInfo>> rankList = playerInfos;
    std::sort(rankList.begin(), rankList.end(), [](std::shared_ptr<PlayerInfo> a, std::shared_ptr<PlayerInfo> b) {
        return a->getArmyNum() > b->getArmyNum() || (a->getArmyNum() == b->getArmyNum() && a->getLandNum() > b->getLandNum());
    });
    return std::make_shared<QVector<std::shared_ptr<PlayerInfo>>>(rankList);
}

void GeneralsGameModel::setPlayerName(const QString &nickname) {
    playerName = nickname;
}

void GeneralsGameModel::startGame() {
    if (gameStarted) return;
    generateRandomGame(100, 100, 4); // TODO
    width = playerMap->getWidth();
    height = playerMap->getHeight();
    gameStarted = true;
}

void GeneralsGameModel::setFocus(int x, int y) {
    if (!gameStarted || surrendered || x < 0 || x >= width || y < 0 || y >= height) return;
    focus = std::make_shared<Focus>(x, y);
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
                map[x2][y2]->setType(CITY);
                playerInfos[map[x2][y2]->getOwner()]->setAlive(false);
                changeOwner(map[x2][y2]->getOwner(), playerId);
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
