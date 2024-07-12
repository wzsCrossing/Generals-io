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

bool PlayerInfo::isAlive() {
    // return isAlive_;
    return loseRound_ == -1;
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

void PlayerInfo::setLose(int loseRound) {
    loseRound_ = loseRound;
    isAlive_ = false;
}

int PlayerInfo::getLoseRound() {
    return loseRound_;
}

void PlayerInfo::setSlientRound(int silentRound) {
    silentRound_ = silentRound;
}

void PlayerInfo::setCapital(Point capital) {
    capital_ = capital;
}

Point PlayerInfo::getCapital() {
    return capital_;
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

void PlayerInfo::cancelMove() {
    moveList_.pop_back();
}

void PlayerInfo::clearMoveList() {
    while (!moveList_.empty()) {
        cancelMove();
    }
}
