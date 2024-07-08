#include "gamepage.h"
#include "ui_gamepage.h"
#include <QPushButton>
#include <QIcon>

GamePage::GamePage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GamePage)
{
    ui->setupUi(this);
    this->setWindowTitle("Generals.io");
    this->resize(840, 840);
    for (int i = 0; i < MaxSize; i++)
        for (int j = 0; j < MaxSize; j++) {
            VisualMap[i][j] = new QPushButton(this);
            ArmyNumber[i][j] = new QLabel(this);
            ArmyNumber[i][j]->setStyleSheet("background: transparent");
            ArmyNumber[i][j]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    /*
     * Here is the randomly generated map which is used to test.
     * Please delete them when run the complete game
     */
    for (int i = 0; i < MaxSize; i++)
        for (int j = 0; j < MaxSize; j++) {
            switch (j % 4) {
                case 0 :
                    map[i][j].setType(CellType::MOUNTAIN);
                    break;
                case 1 :
                    map[i][j].setType(CellType::CAPITAL);
                    break;
                case 2 :
                    map[i][j].setType(CellType::CITY);
                    break;
                case 3 :
                    map[i][j].setType(CellType::BLANK);
                    break;
            }
            if (j % 4 != 0 && j != 7) {
                map[i][j].setArmy(i * j + 1);
                map[i][j].setOwner(i / 2);
            }
        }
}

GamePage::~GamePage()
{
    delete ui;
    for (int i = 0; i < MaxSize; i++)
        for (int j = 0; j < MaxSize; j++) {
            delete VisualMap[i][j];
            delete ArmyNumber[i][j];
        }
}

QString GamePage::getColor(int colorId) const{
    QString temp = "QPushButton {border-radius: 0px; border: 1px solid black; background: ";
    switch (colorId) {
        case 0: return temp + "green}";
        case 1: return temp + "#9575CD}";
        case 2: return temp + "#5A7A85}";
        case 3: return temp + "#0021FF}";
        case 4: return temp + "#FF0970}";
        case 5: return temp + "#137FEA}";
        case 6: return temp + "#E243EA}";
        case 7: return temp + "#663AFF}";
        default : return temp + "white}";
    }
}

void GamePage::paintEvent(QPaintEvent *event) {
    int ButtonSize = this->size().rheight();
    if (ButtonSize > this->size().rwidth()) ButtonSize = this->size().rwidth();
    ButtonSize /= (MaxSize * 1.5);
    QFont font("Consolas", ButtonSize / 2.5);
    for (int i = 0; i < MaxSize; i++)
        for (int j = 0; j < MaxSize; j++) {
            VisualMap[i][j]->setGeometry(i * ButtonSize, j * ButtonSize, ButtonSize, ButtonSize);
            ArmyNumber[i][j]->setGeometry(i * ButtonSize, j * ButtonSize, ButtonSize, ButtonSize);
            switch (map[i][j].getType()) {
                case CellType::BLANK :
                    VisualMap[i][j]->setStyleSheet("QPushButton {background: white; border-radius: 0px; border: 1px solid black}");
                    ArmyNumber[i][j]->setText("");
                    break;
                case CellType::CAPITAL :
                    VisualMap[i][j]->setIcon(QIcon(":/General.png"));
                    VisualMap[i][j]->setStyleSheet(getColor(map[i][j].getOwner()));
                    ArmyNumber[i][j]->setText(QString::number(map[i][j].getArmy()));
                    break;
                case CellType::CITY :
                    VisualMap[i][j]->setIcon(QIcon(":/City.png"));
                    VisualMap[i][j]->setStyleSheet(getColor(map[i][j].getOwner()));
                    ArmyNumber[i][j]->setText(QString::number(map[i][j].getArmy()));
                    break;
                case CellType::MOUNTAIN :
                    VisualMap[i][j]->setIcon(QIcon(":/Mountain.png"));
                    VisualMap[i][j]->setStyleSheet("QPushButton {background: grey; border-radius: 0px; border: 1px solid black}");
                    ArmyNumber[i][j]->setText("");
                    break;
            }
            VisualMap[i][j]->setIconSize(QSize(ButtonSize, ButtonSize));
            ArmyNumber[i][j]->setFont(font);
        }
}
