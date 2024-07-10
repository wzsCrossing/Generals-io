#include "GeneralsViewModel.h"

GeneralsViewModel::GeneralsViewModel() :
    m_cmdStartGame(std::make_shared<StartGameCommand>(this)),
    m_cmdSetFocus(std::make_shared<SetFocusCommand>(this)),
    m_cmdMove(std::make_shared<MoveCommand>(this)),
    m_cmdSurrender(std::make_shared<SurrenderCommand>(this)),
    m_sink(std::make_shared<GeneralsViewModelSink>(this)),
    gameTimer(new QTimer(this)) {
    connect(gameTimer, &QTimer::timeout, this, &GeneralsViewModel::updateGame);
}

void GeneralsViewModel::setModel(const std::shared_ptr<GeneralsGameModel>& model) {
    m_GeneralsModel = model;
    m_GeneralsModel->AddPropertyNotification(std::static_pointer_cast<IPropertyNotification>(m_sink));
}

GeneralsGameModel& GeneralsViewModel::getModel() throw() {
    return *m_GeneralsModel;
}

std::shared_ptr<MapInfo> GeneralsViewModel::getMapInfo() throw() {
    return m_GeneralsModel->getMapInfo();
}

std::shared_ptr<ICommandBase> GeneralsViewModel::getStartGameCommand() throw() {
    return std::static_pointer_cast<ICommandBase>(m_cmdStartGame);
}

std::shared_ptr<ICommandBase> GeneralsViewModel::getSetFocusCommand() throw() {
    return std::static_pointer_cast<ICommandBase>(m_cmdSetFocus);
}

std::shared_ptr<ICommandBase> GeneralsViewModel::getMoveCommand() throw() {
    return std::static_pointer_cast<ICommandBase>(m_cmdMove);
}

std::shared_ptr<ICommandBase> GeneralsViewModel::getSurrenderCommand() throw() {
    return std::static_pointer_cast<ICommandBase>(m_cmdSurrender);
}

bool GeneralsViewModel::startGame(const QString &nickname) {
    gameTimer->start(500);
    return m_GeneralsModel->startGame(nickname);
}

bool GeneralsViewModel::setFocus(int x, int y) {
    return m_GeneralsModel->setFocus(x, y);
}

bool GeneralsViewModel::move(int x, int y, Direction dir, bool half) {
    return m_GeneralsModel->move(x, y, dir, half);
}

bool GeneralsViewModel::surrender() {
    return m_GeneralsModel->surrender();
}

void GeneralsViewModel::updateGame() {
    m_GeneralsModel->addRound();
    emit mapChanged();
}