#include "GeneralsViewModel.h"

GeneralsViewModel::GeneralsViewModel() {
}

void GeneralsViewModel::setModel(const std::shared_ptr<GeneralsGameModel>& model) {
    m_GeneralsModel = model;
}

std::shared_ptr<GeneralsGameModel> GeneralsViewModel::getModel() throw() {
    return m_GeneralsModel;
}

std::shared_ptr<MapInfo> GeneralsViewModel::getMapInfo() throw() {
    return m_GeneralsModel->getMapInfo();
}

QString GeneralsViewModel::getPlayerName() {
    return m_GeneralsModel->getPlayerName();
}

std::shared_ptr<QVector<std::shared_ptr<PlayerInfo>>> GeneralsViewModel::getRankList() throw() {
    return m_GeneralsModel->getRankList();
}

void GeneralsViewModel::setPlayerName(const QString &nickname) {
    m_GeneralsModel->setPlayerName(nickname);
}

void GeneralsViewModel::startGameRandom(int playerNum, bool mode) {
    m_GeneralsModel->startGame(playerNum, mode);
    emit mapChanged();
}

void GeneralsViewModel::startGame(int playerNum, bool mode, std::shared_ptr<MapInfo> map) {
    m_GeneralsModel->startGame(playerNum, mode, map);
    emit mapChanged();
}

void GeneralsViewModel::move(int x, int y, Direction dir, bool half) {
    if (m_GeneralsModel->move(0, x, y, dir, half)) {
        m_GeneralsModel->updateArrow();
        emit successfulMove(dir);
    }
}

void GeneralsViewModel::surrender() {
    m_GeneralsModel->surrender(0);
    clearMove();
}

void GeneralsViewModel::cancelMove() {
    m_GeneralsModel->cancelMove(0);
    m_GeneralsModel->updateArrow();
}

void GeneralsViewModel::clearMove() {
    m_GeneralsModel->clearMove(0);
    m_GeneralsModel->updateArrow();
}

void GeneralsViewModel::updateGame() {
    m_GeneralsModel->addBotMove();
    m_GeneralsModel->execMove();
    m_GeneralsModel->updateView();
    m_GeneralsModel->addRound();
    m_GeneralsModel->updateArrow();
    emit mapChanged();
}

void GeneralsViewModel::endGame() {
    m_GeneralsModel->endGame();
}
