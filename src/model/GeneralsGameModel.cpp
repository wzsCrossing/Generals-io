#include "GeneralsGameModel.h"

GeneralsGameModel::GeneralsGameModel() :
    gameStarted(false), surrendered(false), gameMode(0) {
    playerMap = std::make_shared<MapInfo>();
    playerMap->generateRandomMap(0.1, 0.2);
    width = playerMap->getWidth();
    height = playerMap->getHeight();
}

bool GeneralsGameModel::startGame(const QString &nickname) {
    if (gameStarted) return false;
    playerName = nickname;
    gameStarted = true;
    return true;
}

bool GeneralsGameModel::setFocus(int x, int y) {
    if (!gameStarted) return false;
    if (x < 0 || x >= width || y < 0 || y >= height) return false;
    focus = std::make_shared<Focus>(x, y);
    return true;
}

bool GeneralsGameModel::move(int x, int y, Direction dir, bool half) {
    int x_ = x + directions[dir].first, y_ = y + directions[dir].second;
}

void GeneralsGameModel::addRound() {
}