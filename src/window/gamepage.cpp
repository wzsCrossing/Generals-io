#include "gamepage.h"
#include "ui_gamepage.h"
#include <QPushButton>
#include <QIcon>
#include <QPainter>

GamePage::GamePage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GamePage)
    , focus_X(-1)
    , focus_Y(-1)
    , gameTimer(new QTimer(this))
{
    ui->setupUi(this);
    this->setWindowTitle("Generals.io");
    this->resize(1280, 840);
    QPalette pal;
    pal.setColor(QPalette::Window, QColor(QColor::fromRgb(36, 36, 36)));
    this->setPalette(pal);
    for (int i = 0; i < MaxSize; i++)
        for (int j = 0; j < MaxSize; j++) {
            VisualMap[i][j] = new QPushButton(this);
            connect(VisualMap[i][j], &QPushButton::clicked, this, [=]{paintFocus(focus_X, focus_Y, i, j);focus_X = i; focus_Y = j;});
        }
    QFont font("Consolas", 17);
    font.setBold(true);
    ui->ChangeHalf->setFont(font);
    ui->ChangeHalf->setStyleSheet("QPushButton:hover{background:#81D4FA;}"\
                                  "QPushButton:pressed{background:blue;}"\
                                  "QPushButton{background: #029FFF; border-radius: 8px;}");
    ui->ChangeHalf->setText("full");
    connect(ui->ChangeHalf, &QPushButton::clicked, this, [=] {
        half = not half;
        if (half) ui->ChangeHalf->setText("half");
            else ui->ChangeHalf->setText("full");
    });

    ui->surrender->setFont(font);
    ui->surrender->setStyleSheet("QPushButton:hover{background:#81D4FA;}"\
                                  "QPushButton:pressed{background:blue;}"\
                                  "QPushButton{background: #029FFF; border-radius: 8px;}");
    ui->surrender->setText("Surrender");
    connect(ui->surrender, &QPushButton::clicked, this, [=] {emit surrender();});

    this->hide();
}

void GamePage::Init() {

    /*
     * board
     */
    this->show();
    QFont font("Consolas", 17);
    font.setBold(false);
    font.setPointSize(15);
    ui->board->setFont(font);
    ui->board->setReadOnly(true);
    ui->board->setText("Hello! " + playerName + "!");
    ui->board->append("Welcome to Generals.io!");
    ui->board->append("Press W/A/S/D to move up/left/down/right.");
    ui->board->append("After you clicked move mode button, you can press space to change the move mode faster!");
    ui->board->append("Good luck to YOU!");
}

GamePage::~GamePage()
{
    delete ui;
    for (int i = 0, h = map->getHeight(); i < h; i++)
        for (int j = 0, w = map->getWidth(); j < w; j++)
            delete VisualMap[i][j];
}

void GamePage::changeMapInfo() {
    /*
     * Map Construct
     */
    width = map->getWidth();
    height = map->getHeight();
    for (int i = 0; i < MaxSize; i++)
        for (int j = 0; j < MaxSize; j++)
            if (i < height && j < width) VisualMap[i][j]->show();
                else VisualMap[i][j]->hide();
    /*
     * Ranking List
     */

    playerNum = ranklist->size();
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
    URit->setText("Round : " + QString::number(round));
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

    gameTimer->start(500);

    int max = width > height ? width : height;
    int ButtonSize = this->size().rheight();
    if (ButtonSize > this->size().rwidth()) ButtonSize = this->size().rwidth();
    ButtonSize /= (max * 1.2);
    font.setPointSize(ButtonSize / 2.5);
    font.setBold(false);
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            VisualMap[i][j]->setGeometry(i * ButtonSize, j * ButtonSize, ButtonSize, ButtonSize);
            VisualMap[i][j]->setFont(font);
            switch (map->getCell(i, j)->getType()) {
            case CellType::BLANK :
                VisualMap[i][j]->setStyleSheet(getColor(map->getCell(i, j)->getArmy() > 0 ? map->getCell(i, j)->getOwner() : 8, "", false));
                VisualMap[i][j]->setText(map->getCell(i, j)->getArmy() > 0 ? QString::number(map->getCell(i, j)->getArmy()) : "");
                break;
            case CellType::CAPITAL :
                VisualMap[i][j]->setStyleSheet(getColor(map->getCell(i, j)->getOwner(), ":/General.png", false));
                VisualMap[i][j]->setText(QString::number(map->getCell(i, j)->getArmy()));
                break;
            case CellType::CITY :
                VisualMap[i][j]->setStyleSheet(getColor(map->getCell(i, j)->getOwner(), ":/City.png", false));
                VisualMap[i][j]->setText(QString::number(map->getCell(i, j)->getArmy()));
                break;
            case CellType::MOUNTAIN :
                VisualMap[i][j]->setIcon(QIcon(":/Mountain.png"));
                VisualMap[i][j]->setIconSize(QSize(ButtonSize, ButtonSize));
                VisualMap[i][j]->setStyleSheet("QPushButton {background: grey; border-radius: 0px; border: 1px solid black;}");
                break;
            }
        }
}

QString GamePage::getColor(int colorId, const QString &Pic, bool isFocus) const{
    QString temp = isFocus ? "QPushButton{color: white; border-radius: 0px; border: 3px solid black; background: ":
                             "QPushButton{color: white; border-radius: 0px; border: 1px solid black; background: "        ;
    switch (colorId) {
        case 0: return temp + "green; border-image: url(" + Pic + ");}";
        case 1: return temp + "#9575CD; border-image: url(" + Pic + ");}";
        case 2: return temp + "#5A7A85; border-image: url(" + Pic + ");}";
        case 3: return temp + "#0021FF; border-image: url(" + Pic + ");}";
        case 4: return temp + "#FF0970; border-image: url(" + Pic + ");}";
        case 5: return temp + "#137FEA; border-image: url(" + Pic + ");}";
        case 6: return temp + "#E243EA; border-image: url(" + Pic + ");}";
        case 7: return temp + "#663AFF; border-image: url(" + Pic + ");}";
        case 8: return temp + "white; border-image: url(" + Pic + ");}";
        default : return temp + "#303030; border-image: url(" + Pic + ");}";
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
    int max = width > height ? width : height;
    int ButtonSize = this->size().rheight();
    if (ButtonSize > this->size().rwidth()) ButtonSize = this->size().rwidth();
    ButtonSize /= (max * 1.2);
    QFont font("Consolas", ButtonSize / 2.5);
    if (focus_X >= 0 && focus_X < width && focus_Y >= 0 && focus_Y < height) {
        int i = focus_X, j = focus_Y;
        VisualMap[i][j]->setGeometry(i * ButtonSize, j * ButtonSize, ButtonSize, ButtonSize);
        VisualMap[i][j]->setFont(font);
        switch (map->getCell(i, j)->getType()) {
        case CellType::BLANK :
            VisualMap[i][j]->setStyleSheet(getColor(map->getCell(i, j)->getArmy() > 0 ? map->getCell(i, j)->getOwner() : 8, "", true));
            break;
        case CellType::CAPITAL :
            VisualMap[i][j]->setStyleSheet(getColor(map->getCell(i, j)->getOwner(), ":/General-Focus.png", false));
            break;
        case CellType::CITY :
            VisualMap[i][j]->setStyleSheet(getColor(map->getCell(i, j)->getOwner(), ":/City-Focus.png" , false));
            break;
        case CellType::MOUNTAIN :
            VisualMap[i][j]->setIcon(QIcon(":/Mountain.png"));
            VisualMap[i][j]->setIconSize(QSize(ButtonSize, ButtonSize));
            VisualMap[i][j]->setStyleSheet("QPushButton {background: grey; border-radius: 0px; border: 3px solid black;}");
            break;
        }
    }

    /*
     * To construct half button
     */
    font.setBold(true);
    int Half_Button_Width = 80;
    int Half_Button_Height = 40;
    int Half_Button_X = width * ButtonSize / 2 - Half_Button_Width / 2;
    int Half_Button_Y = height * ButtonSize + ButtonSize / 2;
    ui->ChangeHalf->setGeometry(Half_Button_X, Half_Button_Y, Half_Button_Width, Half_Button_Height);

    /*
     * To construct surrender button
     */

    font.setBold(true);
    int Surrender_Button_Width = 140;
    int Surrender_Button_Height = 40;
    int Surrender_Button_X = width * ButtonSize / 2 - Surrender_Button_Width / 2;
    int Surrender_Button_Y = Half_Button_Y + Half_Button_Height + ButtonSize / 2;
    ui->surrender->setGeometry(Surrender_Button_X, Surrender_Button_Y, Surrender_Button_Width, Surrender_Button_Height);

    /*
     * To construct ranking list
     */
    //ui->rankinglist->item(0, 0)->setText("Round : " + QString::number(ranklist))
    ui->rankinglist->move(this->size().rwidth() - ui->rankinglist->size().rwidth(), 0);
    QTableWidget *UR = ui->rankinglist;
    for (int i = 2; i < playerNum + 2; i++) {
        UR->item(i, 0)->setBackground(getBrush((*ranklist)[i - 2]->getPlayerId()));
        UR->item(i, 1)->setBackground(getBrush(8));
        UR->item(i, 2)->setBackground(getBrush(8));
        UR->item(i, 0)->setText((*ranklist)[i - 2]->getNickName());
        if ((*ranklist)[i - 2]->isAlive()) {
            UR->item(i, 1)->setText(QString::number((*ranklist)[i - 2]->getArmyNum()));
            UR->item(i, 2)->setText(QString::number((*ranklist)[i - 2]->getLandNum()));
        } else {
            UR->item(i, 1)->setText("OUT");
            UR->item(i, 2)->setText("OUT");
        }
    }

    /*
     * To construct board
     */
    ui->board->setGeometry((width + 1) * ButtonSize, 50 * (playerNum + 3), this->size().rwidth() - (width + 1) * ButtonSize, this->size().rheight() - 50 * (playerNum + 3));
}

void GamePage::keyPressEvent(QKeyEvent * event) {
    switch (event->key()) {
        case  Qt::Key_W :
            emit moveSignal(focus_X, focus_Y, Direction::UP, half);
            break;
        case Qt::Key_A:
            emit moveSignal(focus_X, focus_Y, Direction::LEFT, half);
            break;
        case Qt::Key_S:
            emit moveSignal(focus_X, focus_Y, Direction::DOWN, half);
            break;
        case Qt::Key_D:
            emit moveSignal(focus_X, focus_Y, Direction::RIGHT, half);
            break;
        case Qt::Key_Space:
            emit ui->ChangeHalf->clicked();
            break;
    }
}

void GamePage::paintFocus(int origin_x, int origin_y, int new_x, int new_y) {
    int max = width > height ? width : height;
    int ButtonSize = this->size().rheight();

    if (ButtonSize > this->size().rwidth()) ButtonSize = this->size().rwidth();
    ButtonSize /= (max * 1.2);
    QFont font("Consolas", ButtonSize / 2.5);
    if (origin_x >= 0 && origin_x < width && origin_y >= 0 && origin_y < height) {
        int i = origin_x, j = origin_y;
        VisualMap[i][j]->setGeometry(i * ButtonSize, j * ButtonSize, ButtonSize, ButtonSize);
        VisualMap[i][j]->setFont(font);
        switch (map->getCell(i, j)->getType()) {
        case CellType::BLANK :
            VisualMap[i][j]->setStyleSheet(getColor(map->getCell(i, j)->getArmy() > 0 ? map->getCell(i, j)->getOwner() : 8, "", false));
            break;
        case CellType::CAPITAL :
            VisualMap[i][j]->setStyleSheet(getColor(map->getCell(i, j)->getOwner(), ":/General.png", false));
            break;
        case CellType::CITY :
            VisualMap[i][j]->setStyleSheet(getColor(map->getCell(i, j)->getOwner(), ":/City.png", false));
            break;
        case CellType::MOUNTAIN :
            VisualMap[i][j]->setIcon(QIcon(":/Mountain.png"));
            VisualMap[i][j]->setIconSize(QSize(ButtonSize, ButtonSize));
            VisualMap[i][j]->setStyleSheet("QPushButton {background: grey; border-radius: 0px; border: 1px solid black;}");
            break;
        }
    }

    if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height) {
        int i = new_x, j = new_y;
        VisualMap[i][j]->setGeometry(i * ButtonSize, j * ButtonSize, ButtonSize, ButtonSize);
        VisualMap[i][j]->setFont(font);
        switch (map->getCell(i, j)->getType()) {
        case CellType::BLANK :
            VisualMap[i][j]->setStyleSheet(getColor(map->getCell(i, j)->getArmy() > 0 ? map->getCell(i, j)->getOwner() : 8, "", true));
            break;
        case CellType::CAPITAL :
            VisualMap[i][j]->setStyleSheet(getColor(map->getCell(i, j)->getOwner(), ":/General-Focus.png", false));
            break;
        case CellType::CITY :
            VisualMap[i][j]->setStyleSheet(getColor(map->getCell(i, j)->getOwner(), ":/City-Focus.png" , false));
            break;
        case CellType::MOUNTAIN :
            VisualMap[i][j]->setIcon(QIcon(":/Mountain.png"));
            VisualMap[i][j]->setIconSize(QSize(ButtonSize, ButtonSize));
            VisualMap[i][j]->setStyleSheet("QPushButton {background: grey; border-radius: 0px; border: 3px solid black;}");
            break;
        }
    }
}

void GamePage::moveFocus(Direction dir) {
    switch (dir) {
        case Direction::UP :
            paintFocus(focus_X, focus_Y, focus_X, focus_Y - 1);
            focus_Y--;
            break;
        case Direction::DOWN :
            paintFocus(focus_X, focus_Y, focus_X, focus_Y + 1);
            focus_Y++;
            break;
        case Direction::LEFT :
            paintFocus(focus_X, focus_Y, focus_X - 1, focus_Y);
            focus_X--;
            break;
        case Direction::RIGHT :
            paintFocus(focus_X, focus_Y, focus_X + 1, focus_Y);
            focus_X++;
            break;
    }
}

void GamePage::playerDie(const QString &playerName) {
    ui->board->append("Oh no! Player " + playerName + " dies!");
}

QTimer* GamePage::getTimer() {
    return gameTimer;
}
