#include "mappage.h"
#include "ui_mappage.h"
#include <QPushButton>

MapPage::MapPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MapPage)
    , gamepage(new GamePage)
{
    ui->setupUi(this);
    this->resize(1280, 840);
    this->setWindowTitle("Generals.io");
    connect(ui->StartGame, &QPushButton::clicked, this, &MapPage::goToGamePage);
    //ui->StartGame->setGeometry();
}

MapPage::~MapPage()
{
    delete ui;
    delete gamepage;
}

void MapPage::goToGamePage() {
    this->hide();
    gamepage->show();
}
