#include "mappage.h"
#include "ui_mappage.h"
#include "generalsviewmodel.h"
#include <QPushButton>
#include <QFont>

MapPage::MapPage(QWidget *parent, QSharedPointer<GeneralsViewModel> ViewModel)
    : QMainWindow(parent)
    , ui(new Ui::MapPage)
    , gamepage(new GamePage)
    , ViewModel(ViewModel)
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
    /*
     * To construct map
     */
    int max = width > height ? width : height;
    int ButtonSize = this->size().rheight();
    if (ButtonSize > this->size().rwidth()) ButtonSize = this->size().rwidth();
    ButtonSize /= (max * 1.2);
    QFont font("Consolas", ButtonSize / 2.5);
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            //VisualMap[i][j]->setGeometry(i * ButtonSize, j * ButtonSize, ButtonSize, ButtonSize);
            //VisualMap[i][j]->setFont(font);
            //VisualMap[i][j]->
            /*switch (map->getCell(i, j)->getType()) {
            case CellType::BLANK :
                VisualMap[i][j]->setStyleSheet(getColor(map->getCell(i, j)->getArmy() > 0 ? map->getCell(i, j)->getOwner() : 8, "", (i == focus_X && j == focus_Y)));
                VisualMap[i][j]->setText(map->getCell(i, j)->getArmy() > 0 ? QString::number(map->getCell(i, j)->getArmy()) : "");
                break;
            case CellType::CAPITAL :
                VisualMap[i][j]->setStyleSheet(getColor(map->getCell(i, j)->getOwner(), (i == focus_X && j == focus_Y) ? ":/General-Focus.png" : ":/General.png", false));
                VisualMap[i][j]->setText(QString::number(map->getCell(i, j)->getArmy()));
                break;
            case CellType::CITY :
                VisualMap[i][j]->setStyleSheet(getColor(map->getCell(i, j)->getOwner(), (i == focus_X && j == focus_Y) ? ":/City-Focus.png" : ":/City.png", false));
                VisualMap[i][j]->setText(QString::number(map->getCell(i, j)->getArmy()));
                break;
            case CellType::MOUNTAIN :
                VisualMap[i][j]->setIcon(QIcon(":/Mountain.png"));
                VisualMap[i][j]->setIconSize(QSize(ButtonSize, ButtonSize));
                if (i == focus_X && j == focus_Y) VisualMap[i][j]->setStyleSheet("QPushButton {background: grey; border-radius: 0px; border: 3px solid black;}");
                else VisualMap[i][j]->setStyleSheet("QPushButton {background: grey; border-radius: 0px; border: 1px solid black;}");
                break;
            }*/
        }
    /*
     * To construct page transfer button
     */
    font.setPointSize(17);
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
