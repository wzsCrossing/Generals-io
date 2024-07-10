#include "GeneralsGameModel.h"

GeneralsGameModel::GeneralsGameModel() :
    gameStarted(false), surrendered(false), gameMode(0), round(0) {
    playerMap = std::make_shared<MapInfo>();
    generateRandomGame(100, 100, 2); // TODO
    width = playerMap->getWidth();
    height = playerMap->getHeight();
}

std::shared_ptr<MapInfo> GeneralsGameModel::getMapInfo() {
    return playerMap;
}

int GeneralsGameModel::getPlayerNum() {
    return cntPlayer;
}

void GeneralsGameModel::generateRandomGame(int cityDense, int mountainDense, int playerNum) {
    cntPlayer = playerNum;
    playerMap->generateRandomMap(cityDense, mountainDense);
    playerMap->capitalDistribution(cntPlayer);
}

QVector<std::shared_ptr<PlayerInfo>> GeneralsGameModel::getRankList() {
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
    std::sort(rankList.begin(), rankList.end(), [](PlayerInfo* a, PlayerInfo* b) {
        return a->getArmyNum() > b->getArmyNum() || (a->getArmyNum() == b->getArmyNum() && a->getLandNum() > b->getLandNum());
    });
    return rankList;
}

void GeneralsGameModel::startGame(const QString &nickname) {
    if (gameStarted) return;
    playerName = nickname;
    gameStarted = true;
}

void GeneralsGameModel::setFocus(int x, int y) {
    if (!gameStarted || surrendered || x < 0 || x >= width || y < 0 || y >= height) return;
    focus = std::make_shared<Focus>(x, y);
}

void GeneralsGameModel::move(int x, int y, Direction dir, bool half) {
    int x_ = x + directions[dir].first, y_ = y + directions[dir].second;
}

void GeneralsGameModel::addRound() {
    if (round % 50 == 0 && round != 0) {
        playerMap->increaseBlankArmy();
    } else if (round % 2 == 0) {
        playerMap->increaseCityArmy();
    }
    round++;
}