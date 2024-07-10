#include "GeneralsApp.h"
#include <memory>
#include <QSharedMemory>

GeneralsApp::GeneralsApp() {
    std::shared_ptr<GeneralsGameModel> model(new GeneralsGameModel);
    std::shared_ptr<GeneralsViewModel> viewModel(new GeneralsViewModel);
    viewModel->setModel(model);

    mainWindow = new MainWindow;
    mapPage = new MapPage;
    gamePage = new GamePage;

   // connect(mainWindow, &MainWindow::goToMapPage, mapPage, &MapPage::show);
}

void GeneralsApp::show() const {
    mainWindow->show();
}

GeneralsApp::~GeneralsApp() {
    delete mainWindow;
}
