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

void GeneralsGameModel::generateRandomGame(int cityDense, int mountainDense, int playerNum) {
    cntPlayer = playerNum;
    playerInfos.push_back(std::make_shared<PlayerInfo>(playerName, 0));
    for (int i = 1; i < cntPlayer; ++i) {
        playerInfos.push_back(std::make_shared<PlayerInfo>("Bot " + QString::number(i), i));
    }
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

void GeneralsGameModel::setPlayerName(const QString &nickname) {
    playerName = nickname;
}

void GeneralsGameModel::startGame() {
    if (gameStarted) return;
    generateRandomGame(100, 100, 2); // TODO
    width = playerMap->getWidth();
    height = playerMap->getHeight();
    gameStarted = true;
}

void GeneralsGameModel::setFocus(int x, int y) {
    if (!gameStarted || surrendered || x < 0 || x >= width || y < 0 || y >= height) return;
    focus = std::make_shared<Focus>(x, y);
}

void GeneralsGameModel::move(int playerID, int x, int y, Direction dir, bool half) {
    int x_ = x + directions[dir].first, y_ = y + directions[dir].second;
    if (x_ < 0 || x_ >= height || y_ < 0 || y_ >= width || playerMap->getCell(x_, y_)->getType() == MOUNTAIN) return;
    playerInfos[playerID]->addMove(x, y, dir, half);
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
        if (!playerMap->moveArmy(player->getPlayerId(), x, y, x_, y_, move.half)) {
            player->clearMoveList();
        }
    }
}