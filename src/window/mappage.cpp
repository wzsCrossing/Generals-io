#include "mappage.h"
#include "ui_mappage.h"
#include "generalsviewmodel.h"
#include <QPushButton>
#include <QFont>

MapPage::MapPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MapPage)
    , gamepage(new GamePage)
{
    ui->setupUi(this);
    this->resize(1280, 840);
    this->setWindowTitle("Generals.io");
    connect(ui->StartGame, &QPushButton::clicked, this, [=] {this->hide();
                                                             gamepage->playerName = playerName;
                                                             gamepage->show();});
    connect(ui->BackToMain, &QPushButton::clicked, this, [=] {emit backToMain();});
}

MapPage::~MapPage()
{
    delete ui;
    delete gamepage;
}

void MapPage::paintEvent(QPaintEvent *event) {
    QFont font("Consolas", 17);
    font.setBold(true);
    int width = this->size().rwidth();
    int height = this->size().rheight();
    int StartGame_Button_Width = 160;
    int StartGame_Button_Height = 40;
    int StartGame_Button_X = width * 0.2;
    int StartGame_Button_Y = height * 0.7;
    ui->StartGame->setGeometry(StartGame_Button_X, StartGame_Button_Y, StartGame_Button_Width, StartGame_Button_Height);
    ui->StartGame->setFont(font);
    ui->StartGame->setStyleSheet("QPushButton:hover{background:#81D4FA;}"\
                                    "QPushButton:pressed{background:blue;}"\
                                    "QPushButton{background: #029FFF; border-radius: 8px;}");

    int BackToMain_Button_Width = 160;
    int BackToMain_Button_Height = 40;
    int BackToMain_Button_X = width * 0.6;
    int BackToMain_Button_Y = height * 0.7;
    ui->BackToMain->setGeometry(BackToMain_Button_X, BackToMain_Button_Y, BackToMain_Button_Width, BackToMain_Button_Height);
    ui->BackToMain->setFont(font);
    ui->BackToMain->setStyleSheet("QPushButton:hover{background:#81D4FA;}"\
                                 "QPushButton:pressed{background:blue;}"\
                                 "QPushButton{background: #029FFF; border-radius: 8px;}");
}
