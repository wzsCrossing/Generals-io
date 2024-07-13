#include "GeneralsApp.h"
#include <memory>

GeneralsApp::GeneralsApp() {
    std::shared_ptr<GeneralsGameModel> model(new GeneralsGameModel);
    viewModel = new GeneralsViewModel;
    viewModel->setModel(model);

    mainWindow = new MainWindow();
    MapPage *mappage = mainWindow->getMapPage();
    GamePage *gamepage = mappage->getGamePage();
    PlaybackPage *playback = gamepage->getPlaybackPage();

    connect(mappage, &MapPage::startGameRandom, viewModel, &GeneralsViewModel::startGameRandom);
    connect(mappage, &MapPage::startGame, viewModel, &GeneralsViewModel::startGame);
    connect(mainWindow, &MainWindow::sendNickname, viewModel, &GeneralsViewModel::setPlayerName);
    connect(gamepage, &GamePage::moveSignal, viewModel, &GeneralsViewModel::move);
    connect(viewModel, &GeneralsViewModel::mapChanged, gamepage, [=]{
        gamepage->setMap(viewModel->getMapInfo());
        gamepage->setRanklist(viewModel->getRankList());
        gamepage->setRound(viewModel->getModel()->getRound());
        gamepage->changeMapInfo();
    });

    connect(viewModel, &GeneralsViewModel::successfulMove, gamepage, &GamePage::moveFocus);
    connect(gamepage->getTimer(), &QTimer::timeout, viewModel, &GeneralsViewModel::updateGame);
    connect(gamepage, &GamePage::surrender, viewModel, &GeneralsViewModel::surrender);
    connect(gamepage, &GamePage::gameEnded, viewModel, &GeneralsViewModel::endGame);
    connect(gamepage, &GamePage::undo, viewModel, &GeneralsViewModel::cancelMove);
    connect(gamepage, &GamePage::clearMove, viewModel, &GeneralsViewModel::clearMove);
    connect(playback, &PlaybackPage::roundSignal, playback, [=](int round) {playback->changeMapInfo(viewModel->getPlaybackMapInfo(round));});
}

void GeneralsApp::show() const {
    mainWindow->show();
}

GeneralsApp::~GeneralsApp() {
    delete mainWindow;
}
