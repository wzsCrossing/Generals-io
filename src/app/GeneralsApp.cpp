#include "GeneralsApp.h"
#include <memory>
#include <QSharedMemory>

GeneralsApp::GeneralsApp() {
    std::shared_ptr<GeneralsGameModel> model(new GeneralsGameModel);
    GeneralsViewModel *viewModel = new GeneralsViewModel;
    viewModel->setModel(model);

    mainWindow = new MainWindow();
    MapPage *mappage = mainWindow->getMapPage();
    GamePage *gamepage = mappage->getGamePage();
    connect(mainWindow, &MainWindow::startGame, viewModel, &GeneralsViewModel::startGame);
    connect(mainWindow, &MainWindow::sendNickname, viewModel, &GeneralsViewModel::setPlayerName);
    connect(mainWindow, &MainWindow::sendNickname, viewModel, &GeneralsViewModel::setPlayerName);
    connect(gamepage, &GamePage::moveSignal, viewModel, &GeneralsViewModel::move);
    connect(viewModel, &GeneralsViewModel::mapChanged, gamepage, &GamePage::Init);
    connect(viewModel, &GeneralsViewModel::successfulMove, gamepage, &GamePage::moveFocus);
    connect(viewModel, &GeneralsViewModel::playerDie, gamepage, &GamePage::playerDie);
}

void GeneralsApp::show() const {
    mainWindow->show();
}

GeneralsApp::~GeneralsApp() {
    delete mainWindow;
}
