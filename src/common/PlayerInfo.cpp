#include "PlayerInfo.h"

QString PlayerInfo::getNickName() {
    return nickName_;
}

int PlayerInfo::getLandNum() {
    return landNum_;
}

int PlayerInfo::getArmyNum() {
    return armyNum_;
}

int PlayerInfo::getPlayerId() {
    return playerId_;
}

bool PlayerInfo::isReady() {
    return isReady_;
}

bool PlayerInfo::isAlive() {
    return isAlive_;
}

int PlayerInfo::getSlientRound() {
    return silentRound_;
}

void PlayerInfo::setLandNum(int landNum) {
    landNum_ = landNum;
}

void PlayerInfo::setArmyNum(int armyNum) {
    armyNum_ = armyNum;
}

void PlayerInfo::setReady(bool isReady) {
    isReady_ = isReady;
}

void PlayerInfo::setAlive(bool isAlive) {
    isAlive_ = isAlive;
}

void PlayerInfo::setSlientRound(int silentRound) {
    silentRound_ = silentRound;
}

void PlayerInfo::addMove(int x, int y, Direction dir, bool half) {
    moveList_.push_back((Move) {x, y, dir, half});
}

Move PlayerInfo::getFirstMove() {
    auto move = moveList_.front();
    moveList_.pop_front();
    return move;
}

bool PlayerInfo::hasMove() {
    return !moveList_.empty();
}

void PlayerInfo::clearMoveList() {
    moveList_.clear();
}
