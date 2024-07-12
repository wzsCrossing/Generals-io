#include "mappage.h"
#include "ui_mappage.h"
#include <QPushButton>
#include <QFont>
#include <QMessageBox>

MapPage::MapPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MapPage)
    , gamepage(new GamePage)
    , map(new MapInfo(MaxSize, MaxSize))
{
    map->generateRandomMap(0, 0);
    ui->setupUi(this);
    this->resize(1280, 840);
    this->setWindowTitle("Generals.io");
    QPalette pal;
    pal.setColor(QPalette::Window, QColor(QColor::fromRgb(36, 36, 36)));
    this->setPalette(pal);

    connect(ui->StartGame, &QPushButton::clicked, this, [=] {this->hide();
                                                             emit startGame();
                                                             gamepage->playerName = playerName;
                                                             gamepage->Init();
                                                            });
    connect(ui->BackToMain, &QPushButton::clicked, this, [=] {emit backToMain();});
    connect(gamepage, &GamePage::surrender, this, [=] {this->show();gamepage->hide();});

    ui->heightInput->setText("25");
    ui->widthInput->setText("25");
    connect(ui->heightInput, &QLineEdit::editingFinished, this, [=] {
        int h = ui->heightInput->text().toInt();
        if (h < 16 || h > 25) {
            QMessageBox::information(this, "Warning", "Invalid height! The height must be an integer between 16 and 25!");
            ui->heightInput->setText("");
        } else this->height = ui->heightInput->text().toInt();
        changeMap();
    });
    connect(ui->widthInput, &QLineEdit::editingFinished, this, [=] {
        int w = ui->widthInput->text().toInt();
        if (w < 16 || w > 25) {
            QMessageBox::information(this, "Warning", "Invalid width! The width must be an integer between 16 and 25!");
            ui->widthInput->setText("");
        } else this->width = ui->widthInput->text().toInt();
        changeMap();
    });

    for (int i = 0; i < MaxSize; i++)
        for (int j = 0; j < MaxSize; j++) {
            VisualMap[i][j] = new QPushButton(this);
            connect(VisualMap[i][j], &QPushButton::clicked, this, [=] {
                switch (map->getCell(i, j)->getType()) {
                case CellType::BLANK :
                    map->getCell(i, j)->setType(CellType::CITY);
                    break;
                case CellType::CITY :
                    map->getCell(i, j)->setType(CellType::MOUNTAIN);
                    break;
                case CellType::MOUNTAIN :
                    map->getCell(i, j)->setType(CellType::BLANK);
                    break;
                case CellType::CAPITAL :
                    break;
                }
                drawVisualMap(i, j);
            });
        }

    QFont font("Consolas", 17);
    ui->heightLabel->setFont(font);
    ui->heightLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->heightLabel->setStyleSheet("color: #81D4FA");
    ui->heightLabel->resize(120, 40);

    ui->heightInput->setFont(font);
    ui->heightInput->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->heightInput->resize(120, 40);

    ui->widthLabel->setFont(font);
    ui->widthLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->widthLabel->setStyleSheet("color: #81D4FA");
    ui->widthLabel->resize(120, 40);

    ui->widthInput->setFont(font);
    ui->widthInput->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->widthInput->resize(120, 40);

    changeMap();
}

MapPage::~MapPage()
{
    delete ui;
    delete gamepage;
    for (int i = 0; i < MaxSize; i++)
        for (int j = 0; j < MaxSize; j++)
            delete VisualMap[i][j];
}

GamePage* MapPage::getGamePage() {
    return gamepage;
}

QString MapPage::getColor(int colorId, const QString &Pic) const{
    QString temp = "QPushButton{color: white; border-radius: 0px; border: 1px solid black; background: ";
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

QBrush MapPage::getBrush(int colorId) const {
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

void MapPage::changeMap() {
    for (int i = 0; i < MaxSize; i++)
        for (int j = 0; j < MaxSize; j++)
            if (i < height && j < width) {
                VisualMap[i][j]->show();
                drawVisualMap(i, j);
            } else
                VisualMap[i][j]->hide();
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
    /*
     * To construct page transfer button
     */
    font.setPointSize(17);
    font.setBold(true);
    int windowWidth = this->size().rwidth();
    int windowHeight = this->size().rheight();
    int StartGame_Button_Width = 160;
    int StartGame_Button_Height = 40;
    int StartGame_Button_X = windowWidth * 0.2;
    int StartGame_Button_Y = windowHeight * 0.9;
    ui->StartGame->setGeometry(StartGame_Button_X, StartGame_Button_Y, StartGame_Button_Width, StartGame_Button_Height);
    ui->StartGame->setFont(font);
    ui->StartGame->setStyleSheet("QPushButton:hover{background:#81D4FA;}"\
                                    "QPushButton:pressed{background:blue;}"\
                                    "QPushButton{background: #029FFF; border-radius: 8px;}");

    int BackToMain_Button_Width = 160;
    int BackToMain_Button_Height = 40;
    int BackToMain_Button_X = windowWidth * 0.6;
    int BackToMain_Button_Y = windowHeight * 0.9;
    ui->BackToMain->setGeometry(BackToMain_Button_X, BackToMain_Button_Y, BackToMain_Button_Width, BackToMain_Button_Height);
    ui->BackToMain->setFont(font);
    ui->BackToMain->setStyleSheet("QPushButton:hover{background:#81D4FA;}"\
                                 "QPushButton:pressed{background:blue;}"\
                                 "QPushButton{background: #029FFF; border-radius: 8px;}");

    ui->heightLabel->move(ButtonSize * width + windowWidth * 0.03, windowHeight * 0.01);
    ui->heightInput->move(ButtonSize * width + ui->heightLabel->width() + windowWidth * 0.04, windowHeight * 0.01);
    ui->widthLabel->move(ButtonSize * width + ui->heightLabel->width() + ui->heightInput->width() + windowWidth * 0.05, windowHeight * 0.01);
    ui->widthInput->move(ButtonSize * width + ui->heightLabel->width() + ui->heightInput->width() + ui->widthLabel->width() + windowWidth * 0.06, windowHeight * 0.01);
}

void MapPage::drawVisualMap(int i, int j) {
    int max = width > height ? width : height;
    int ButtonSize = this->size().rheight();
    if (ButtonSize > this->size().rwidth()) ButtonSize = this->size().rwidth();
    ButtonSize /= (max * 1.2);
    QFont font("Consolas", 17);
    VisualMap[i][j]->setGeometry(j * ButtonSize, i * ButtonSize, ButtonSize, ButtonSize);
    VisualMap[i][j]->setFont(font);
    switch (map->getCell(i, j)->getType()) {
        case CellType::BLANK :
            VisualMap[i][j]->setIcon(QIcon());
            VisualMap[i][j]->setStyleSheet(getColor(8, ""));
            break;
        case CellType::CITY :
            VisualMap[i][j]->setStyleSheet(getColor(map->getCell(i, j)->getOwner(), ":/City.png"));
            break;
        case CellType::MOUNTAIN :
            VisualMap[i][j]->setIcon(QIcon(":/Mountain.png"));
            VisualMap[i][j]->setIconSize(QSize(ButtonSize, ButtonSize));
            VisualMap[i][j]->setStyleSheet("QPushButton {background: grey; border-radius: 0px; border: 1px solid black;}");
            break;
        case CellType::CAPITAL :
            break;
    }
}
