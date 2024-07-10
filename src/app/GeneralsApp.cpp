#include "GeneralsApp.h"
#include <memory>

GeneralsApp::GeneralsApp() {
    std::shared_ptr<GeneralsGameModel> model(new GeneralsGameModel);
    std::shared_ptr<GeneralsViewModel> viewModel(new GeneralsViewModel);
    viewModel->setModel(model);

    mainWindow = new MainWindow(nullptr, viewModel);
}

void GeneralsApp::show() const {
    mainWindow->show();
}

GeneralsApp::~GeneralsApp() {
    delete mainWindow;
}
