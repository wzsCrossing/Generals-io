#include "gamepage.h"
#include "ui_gamepage.h"
#include <QPushButton>
#include <QIcon>

GamePage::GamePage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GamePage)
    , map(new MapInfo(20, 20))
{
    /*
     * Map Construct
     */
    int playerNum = 8;
    ui->setupUi(this);
    this->setWindowTitle("Generals.io");
    this->resize(1280, 840);
    int width = map->getWidth();
    int height = map->getHeight();
    map->generateRandomMap(80, 80);
    map->capitalDistribution(playerNum);
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            VisualMap[i][j] = new QPushButton(this);
            connect(VisualMap[i][j], &QPushButton::clicked, this, [=] {setFocusSignal(i, j);});
            ArmyNumber[i][j] = new QLabel(this);
            ArmyNumber[i][j]->setStyleSheet("background: transparent");
            ArmyNumber[i][j]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    /*
     * Ranking List
     */
    QTableWidget *UR = ui->rankinglist;
    QFont font("Consolas", 20);
    font.setBold(true);
    UR->setSelectionMode(QAbstractItemView::NoSelection);
    UR->setEditTriggers(QAbstractItemView::NoEditTriggers);
    UR->verticalHeader()->setVisible(false);
    UR->horizontalHeader()->setVisible(false);
    UR->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    UR->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    UR->setColumnCount(3);
    UR->setColumnWidth(0, 160);
    UR->setColumnWidth(1, 160);
    UR->setColumnWidth(2, 160);
    UR->setRowCount(playerNum + 2);
    for (int i = 0; i < playerNum + 2; i++)
        UR->setRowHeight(i, 50);
    UR->setSpan(0, 0, 1, 3);
    UR->resize(480, (playerNum + 2) * 50);

    UR->setItem(0, 0, new QTableWidgetItem);
    QTableWidgetItem *URit = UR->item(0, 0);
    URit->setText("Round : 0");
    URit->setBackground(getBrush(-1));
    URit->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    URit->setFont(font);

    UR->setItem(1, 0, new QTableWidgetItem);
    URit = UR->item(1, 0);
    URit->setText("Name");
    URit->setBackground(getBrush(-1));
    URit->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    URit->setFont(font);

    UR->setItem(1, 1, new QTableWidgetItem);
    URit = UR->item(1, 1);
    URit->setText("Army");
    URit->setBackground(getBrush(-1));
    URit->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    URit->setFont(font);

    UR->setItem(1, 2, new QTableWidgetItem);
    URit = UR->item(1, 2);
    URit->setText("Land");
    URit->setBackground(getBrush(-1));
    URit->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    URit->setFont(font);

    for (int i = 2; i < playerNum + 2; i++)
        for (int j = 0; j < 3; j++) {
            UR->setItem(i, j, new QTableWidgetItem);
            URit = UR->item(i, j);
            URit->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            URit->setFont(font);
        }

    /*
     * Board
     */
    //ui->boardcast->
}

GamePage::~GamePage()
{
    delete ui;
    for (int i = 0, h = map->getHeight(); i < h; i++)
        for (int j = 0, w = map->getWidth(); j < w; j++) {
            delete VisualMap[i][j];
            delete ArmyNumber[i][j];
        }
    delete map;
}

void GamePage::setFocusSignal(int x, int y) {
    emit focusSignal(x, y);
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
        default : return temp + "#303030}";
    }
}

QBrush GamePage::getBrush(int colorId) const {
    QBrush brush(Qt::SolidPattern);
    switch (colorId) {
        case 0: brush.setColor(QColor::fromRgb(0x00, 0x80, 0x00));break;
        case 1: brush.setColor(QColor::fromRgb(0x95, 0x75, 0xCD));break;
        case 2: brush.setColor(QColor::fromRgb(0x5A, 0x7A, 0x85));break;
        case 3: brush.setColor(QColor::fromRgb(0x00, 0x21, 0xFF));break;
        case 4: brush.setColor(QColor::fromRgb(0xFF, 0x09, 0x70));break;
        case 5: brush.setColor(QColor::fromRgb(0x13, 0x7F, 0xEA));break;
        case 6: brush.setColor(QColor::fromRgb(0xE2, 0x43, 0xEA));break;
        case 7: brush.setColor(QColor::fromRgb(0x66, 0x3A, 0xFF));break;
        case 8: brush.setColor(QColor::fromRgb(0x4D, 0x4D, 0x4D));break;
        default : brush.setColor(QColor::fromRgb(0x80, 0x80, 0x80));break;
    }
    return brush;
}

void GamePage::paintEvent(QPaintEvent *event) {
    /*
     * To construct map
     */
    int width = map->getWidth();
    int height = map->getHeight();
    int max = width > height ? width : height;
    int ButtonSize = this->size().rheight();
    if (ButtonSize > this->size().rwidth()) ButtonSize = this->size().rwidth();
    ButtonSize /= (max * 1.2);
    QFont font("Consolas", ButtonSize / 2.5);
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            VisualMap[i][j]->setGeometry(i * ButtonSize, j * ButtonSize, ButtonSize, ButtonSize);
            ArmyNumber[i][j]->setGeometry(i * ButtonSize, j * ButtonSize, ButtonSize, ButtonSize);
            switch (map->getCell(i, j)->getType()) {
                case CellType::BLANK :
                VisualMap[i][j]->setStyleSheet(map->getCell(i, j)->getArmy() > 0 ? getColor(map->getCell(i, j)->getOwner()) : "QPushButton {background: white; border-radius: 0px; border: 1px solid black}");
                    ArmyNumber[i][j]->setText(map->getCell(i, j)->getArmy() > 0 ? QString::number(map->getCell(i, j)->getArmy()) : "");
                    break;
                case CellType::CAPITAL :
                    VisualMap[i][j]->setIcon(QIcon(":/General.png"));
                    VisualMap[i][j]->setStyleSheet(getColor(map->getCell(i, j)->getOwner()));
                    ArmyNumber[i][j]->setText(QString::number(map->getCell(i, j)->getArmy()));
                    break;
                case CellType::CITY :
                    VisualMap[i][j]->setIcon(QIcon(":/City.png"));
                    VisualMap[i][j]->setStyleSheet(getColor(map->getCell(i, j)->getOwner()));
                    ArmyNumber[i][j]->setText(QString::number(map->getCell(i, j)->getArmy()));
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
    /*
     * To construct ranking list
     */
    ui->rankinglist->move(this->size().rwidth() - ui->rankinglist->size().rwidth(), 0);
    int playerNum= 8;
    int playerList[8];
    for (int i = 0; i < 8; i++) playerList[i] = i;
    QTableWidget *UR = ui->rankinglist;
    for (int i = 2; i < playerNum + 2; i++) {
        UR->item(i, 0)->setBackground(getBrush(playerList[i - 2]));
        UR->item(i, 1)->setBackground(getBrush(8));
        UR->item(i, 2)->setBackground(getBrush(8));
        UR->item(i, 0)->setText(QString(char(i + 65)));
        UR->item(i, 1)->setText("1");
        UR->item(i, 2)->setText("1");
    }
}
