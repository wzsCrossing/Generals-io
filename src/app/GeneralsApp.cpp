#include "GeneralsApp.h"
#include <memory>
#include <QSharedMemory>

GeneralsApp::GeneralsApp() {
    std::shared_ptr<GeneralsGameModel> model(new GeneralsGameModel);
    std::shared_ptr<GeneralsViewModel> viewModel(new GeneralsViewModel);
    viewModel->setModel(model);

    GeneralsViewModel* ptr = viewModel.get();
    QSharedPointer<GeneralsViewModel> sharedViewModel(ptr);
    mainWindow = new MainWindow(nullptr, sharedViewModel);
}

void GeneralsApp::show() const {
    mainWindow->show();
}

GeneralsApp::~GeneralsApp() {
    delete mainWindow;
}
