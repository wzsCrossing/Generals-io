#include "GeneralsApp.h"
#include <memory>
#include <QSharedMemory>

GeneralsApp::GeneralsApp() {
    std::shared_ptr<GeneralsGameModel> model(new GeneralsGameModel);
    GeneralsViewModel *viewModel = new GeneralsViewModel;
    viewModel->setModel(model);

    mainWindow = new MainWindow();
    connect(mainWindow, &MainWindow::startGame, viewModel, &GeneralsViewModel::startGame);
    connect(mainWindow, &MainWindow::sendNickname, viewModel, &GeneralsViewModel::setPlayerName);
    connect(viewModel, &GeneralsViewModel::gameStarted, mainWindow, &MainWindow::initFinished);
    connect(mainWindow, &MainWindow::sendNickname, viewModel, &GeneralsViewModel::setPlayerName);
}

void GeneralsApp::show() const {
    mainWindow->show();
}

GeneralsApp::~GeneralsApp() {
    delete mainWindow;
}
