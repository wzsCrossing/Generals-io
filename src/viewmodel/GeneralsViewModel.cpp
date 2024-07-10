#include "GeneralsViewModel.h"

GeneralsViewModel::GeneralsViewModel() : gameTimer(new QTimer(this)) {
    connect(gameTimer, &QTimer::timeout, this, &GeneralsViewModel::updateGame);
}

void GeneralsViewModel::setModel(const std::shared_ptr<GeneralsGameModel>& model) {
    m_GeneralsModel = model;
}

GeneralsGameModel& GeneralsViewModel::getModel() throw() {
    return *m_GeneralsModel;
}

std::shared_ptr<MapInfo> GeneralsViewModel::getMapInfo() throw() {
    return m_GeneralsModel->getMapInfo();
}

QVector<std::shared_ptr<PlayerInfo>> GeneralsViewModel::getRankList() throw() {
    return m_GeneralsModel->getRankList();
}

void GeneralsViewModel::setPlayerName(const QString &nickname) {
    m_GeneralsModel->setPlayerName(nickname);
}

void GeneralsViewModel::startGame() {
    m_GeneralsModel->startGame();
    gameTimer->start(500);
    emit gameStarted(this->getMapInfo(), this->getRankList());
}

void GeneralsViewModel::setFocus(int x, int y) {
    m_GeneralsModel->setFocus(x, y);
}

void GeneralsViewModel::move(int x, int y, Direction dir, bool half) {
    m_GeneralsModel->move(0, x, y, dir, half);
}

void GeneralsViewModel::surrender() {
    // m_GeneralsModel->surrender();
}

void GeneralsViewModel::updateGame() {
    m_GeneralsModel->execMove();
    m_GeneralsModel->addRound();
    emit mapChanged();
}
