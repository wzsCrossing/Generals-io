#pragma once

#include "GeneralsGameModel.h"
#include "GeneralsViewModel.h"
#include "mainwindow.h"
#include "mappage.h"
#include "gamepage.h"

class GeneralsApp : public QObject {
    Q_OBJECT
public:
    explicit GeneralsApp();
    void show() const;
    ~GeneralsApp();
private:
    MainWindow* mainWindow;
    GamePage* gamePage;
    MapPage* mapPage;
};
