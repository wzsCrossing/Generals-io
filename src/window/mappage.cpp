#include "mappage.h"
#include "ui_mappage.h"
#include <QPushButton>
#include <QFont>

MapPage::MapPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MapPage)
{
    ui->setupUi(this);
    this->resize(1280, 840);
    this->setWindowTitle("Generals.io");
    this->show();
}

MapPage::~MapPage()
{
    delete ui;
}

void MapPage::show() {
    this->show();
}

void MapPage::paintEvent(QPaintEvent *event) {
    /*
     * To construct map
     */
    qDebug() << "No" <<Qt::endl;
    int max = width > height ? width : height;
    int ButtonSize = this->size().rheight();
    if (ButtonSize > this->size().rwidth()) ButtonSize = this->size().rwidth();
    ButtonSize /= (max * 1.2);
    QFont font("Consolas", ButtonSize / 2.5);
    font.setBold(true);
    int width = this->size().rwidth();
    int height = this->size().rheight();
    int StartGame_Button_Width = 160;
    int StartGame_Button_Height = 40;
    int StartGame_Button_X = width * 0.2;
    int StartGame_Button_Y = height * 0.9;
    ui->StartGame->setGeometry(StartGame_Button_X, StartGame_Button_Y, StartGame_Button_Width, StartGame_Button_Height);
    ui->StartGame->setFont(font);
    ui->StartGame->setStyleSheet("QPushButton:hover{background:#81D4FA;}"\
                                    "QPushButton:pressed{background:blue;}"\
                                    "QPushButton{background: #029FFF; border-radius: 8px;}");

    int BackToMain_Button_Width = 160;
    int BackToMain_Button_Height = 40;
    int BackToMain_Button_X = width * 0.6;
    int BackToMain_Button_Y = height * 0.9;
    ui->BackToMain->setGeometry(BackToMain_Button_X, BackToMain_Button_Y, BackToMain_Button_Width, BackToMain_Button_Height);
    ui->BackToMain->setFont(font);
    ui->BackToMain->setStyleSheet("QPushButton:hover{background:#81D4FA;}"\
                                 "QPushButton:pressed{background:blue;}"\
                                 "QPushButton{background: #029FFF; border-radius: 8px;}");
}
