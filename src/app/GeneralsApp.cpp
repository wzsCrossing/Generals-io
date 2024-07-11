#include "GeneralsApp.h"
#include <memory>

GeneralsApp::GeneralsApp() {
    std::shared_ptr<GeneralsGameModel> model(new GeneralsGameModel);
    viewModel = new GeneralsViewModel;
    viewModel->setModel(model);

    mainWindow = new MainWindow();
    MapPage *mappage = mainWindow->getMapPage();
    GamePage *gamepage = mappage->getGamePage();

    connect(mainWindow, &MainWindow::startGame, viewModel, &GeneralsViewModel::startGame);
    connect(mainWindow, &MainWindow::sendNickname, viewModel, &GeneralsViewModel::setPlayerName);
    connect(mainWindow, &MainWindow::sendNickname, viewModel, &GeneralsViewModel::setPlayerName);
    connect(gamepage, &GamePage::moveSignal, viewModel, &GeneralsViewModel::move);
    connect(viewModel, &GeneralsViewModel::mapChanged, gamepage, [=]{
        gamepage->setMap(viewModel->getMapInfo());
        gamepage->setRanklist(viewModel->getRankList());
        gamepage->setRound(viewModel->getModel()->getRound());
        gamepage->changeMapInfo();
    });

    connect(viewModel, &GeneralsViewModel::successfulMove, gamepage, &GamePage::moveFocus);
    connect(viewModel, &GeneralsViewModel::playerDie, gamepage, &GamePage::playerDie);
    connect(gamepage->getTimer(), &QTimer::timeout, viewModel, &GeneralsViewModel::updateGame);
}

void GeneralsApp::show() const {
    mainWindow->show();
}

GeneralsApp::~GeneralsApp() {
    delete mainWindow;
}
