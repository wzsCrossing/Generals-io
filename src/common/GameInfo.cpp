#include "GameInfo.h"

static int dx[] = {-1, 1, 0, 0};
static int dy[] = {0, 0, -1, 1};

GameInfo::~GameInfo() {
    delete map_;
    for (auto player : players_) {
        delete player;
    }
}

void GameInfo::importGame(const QString& fileName, int width, int height) {

}

void GameInfo::exportGame(const QString& fileName) {

}

void GameInfo::generateRandomGame(int cityDense, int mountainDense) {
    map_->generateRandomMap(cityDense, mountainDense);
    map_->capitalDistribution(playerNum_);
}

MapInfo* GameInfo::getMap() {
    return map_;
}

int GameInfo::getPlayerNum() {
    return playerNum_;
}

PlayerInfo* GameInfo::getPlayer(int playerId) {
    return players_[playerId];
}

QVector<PlayerInfo*> GameInfo::getRankList() {
    for (auto& player : players_) {
        player->setLandNum(0);
        player->setArmyNum(0);
    }

    int height = map_->getHeight();
    int width = map_->getWidth();
    auto map = map_->getMap();
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            auto cell = map[i][j];
            if (cell->getOwner() == -1) {
                continue;
            }

            int playerId = cell->getOwner();
            auto player = getPlayer(playerId);
            player->setLandNum(player->getLandNum() + 1);
            player->setArmyNum(player->getArmyNum() + cell->getArmy());
        }
    }

    QVector<PlayerInfo*> rankList(players_);
    std::sort(rankList.begin(), rankList.end(), [](PlayerInfo* a, PlayerInfo* b) {
        return a->getArmyNum() > b->getArmyNum() || (a->getArmyNum() == b->getArmyNum() && a->getLandNum() > b->getLandNum());
    });

    return rankList;
}

void GameInfo::addPlayer(const QString& nickName) {
    players_.push_back(new PlayerInfo(nickName, playerNum_++));
}

void GameInfo::excuteMove() {
    for (auto& player : players_) {
        if (!player->isAlive()) {
            continue;
        }

        if (!player->hasMove()) {
            player->setSlientRound(player->getSlientRound() + 1);
            continue;
        } else {
            player->setSlientRound(0);
        }

        auto move = player->getFirstMove();
        int x = move.x, y = move.y;
        int nx = x + dx[move.dir], ny = y + dy[move.dir];
        if (!map_->moveArmy(player->getPlayerId(), x, y, nx, ny, move.half)) {
            player->clearMoveList();
        }
    }
}

void GameInfo::addMove(int playerId, int x, int y, Direction dir, int mode) {
    int nx = x + dx[dir];
    int ny = y + dy[dir];

    if (nx < 0 || nx >= map_->getHeight() || ny < 0 || ny >= map_->getWidth() || map_->getCell(nx, ny)->getType() == MOUNTAIN) {
        return;
    }

    players_[playerId]->addMove(x, y, dir, mode);
}
