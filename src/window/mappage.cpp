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

    connect(ui->StartGame, &QPushButton::clicked, this, [=] {
        this->hide();
        if (ui->isRandom->isChecked()) emit startGameRandom(ui->playerNumberInput->text().toInt(), ui->isFrog->isChecked());
        else {
            map->setHeight(height);
            map->setWidth(width);
            emit startGame(ui->playerNumberInput->text().toInt(), ui->isFrog->isChecked(), map);
        }
        gamepage->setMode(ui->isVisible->isChecked(), ui->isSilent->isChecked());
        gamepage->playerName = playerName;
        gamepage->Init();
    });
    connect(ui->BackToMain, &QPushButton::clicked, this, [=] {emit backToMain();});
    connect(gamepage, &GamePage::gameEnded, this, [=] {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                map->getCell(i, j)->setArmy(0);
                map->getCell(i, j)->setOwner(-1);
                if (map->getCell(i, j)->getType() == CellType::CAPITAL) {
                    map->getCell(i, j)->setType(CellType::BLANK);
                }
            }
        }
        this->show();
        gamepage->hide();
        changeMap();
    });

    ui->heightInput->setText("25");
    ui->widthInput->setText("25");
    ui->playerNumberInput->setText("8");
    ui->playerNameInput->setDisabled(true);
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
    connect(ui->playerNumberInput, &QLineEdit::editingFinished, this, [=] {
        int num = ui->playerNumberInput->text().toInt();
        if (num < 2 || num > 8) {
            QMessageBox::information(this, "Warning", "Invalid player number! The number must be an integer between 2 and 8!");
            ui->playerNumberInput->setText("");
        }
    });

    for (int i = 0; i < MaxSize; i++)
        for (int j = 0; j < MaxSize; j++) {
            VisualMap[i][j] = new QPushButton(this);
            connect(VisualMap[i][j], &QPushButton::clicked, this, [=] {
                if (!ui->isRandom->isChecked()) {
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

    ui->playerNumberLabel->setFont(font);
    ui->playerNumberLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->playerNumberLabel->setStyleSheet("color: #81D4FA");
    ui->playerNumberLabel->resize(200, 40);

    ui->playerNumberInput->setFont(font);
    ui->playerNumberInput->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->playerNumberInput->resize(120, 40);

    ui->playerNameLabel->setFont(font);
    ui->playerNameLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->playerNameLabel->setStyleSheet("color: #81D4FA");
    ui->playerNameLabel->resize(200, 40);

    ui->playerNameInput->setFont(font);
    ui->playerNameInput->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->playerNameInput->resize(160, 40);

    ui->isRandom->setFont(font);
    ui->isRandom->resize(160, 40);
    ui->isRandom->setStyleSheet("QCheckBox{color: white} QCheckBox::indicator:checked{border-radius: 5px; background: #81D4FA;}");
    connect(ui->isRandom, &QCheckBox::checkStateChanged, this, [=] {
        if (ui->isRandom->isChecked()) {
            ui->heightInput->setDisabled(true);
            ui->widthInput->setDisabled(true);
        } else {
            ui->heightInput->setDisabled(false);
            ui->widthInput->setDisabled(false);
        }
    });

    font.setPointSize(14);

    ui->isVisible->setFont(font);
    ui->isVisible->resize(160, 40);
    ui->isVisible->setStyleSheet("QCheckBox{color: white} QCheckBox::indicator:checked{border-radius: 5px; background: #81D4FA;}");
    connect(ui->isVisible, &QCheckBox::checkStateChanged, this, [=] {
        if (ui->isVisible->isChecked()) ui->isVisible->setText("Crystal Clear");
        else ui->isVisible->setText("Misty Veil");
    });

    ui->isSilent->setFont(font);
    ui->isSilent->resize(180, 40);
    ui->isSilent->setStyleSheet("QCheckBox{color: white} QCheckBox::indicator:checked{border-radius: 5px; background: #81D4FA;}");
    connect(ui->isSilent, &QCheckBox::checkStateChanged, this, [=] {
        if (ui->isSilent->isChecked()) ui->isSilent->setText("Silent War");
        else ui->isSilent->setText("Not Silent War");
    });

    ui->isFrog->setFont(font);
    ui->isFrog->resize(160, 40);
    ui->isFrog->setStyleSheet("QCheckBox{color: white} QCheckBox::indicator:checked{border-radius: 5px; background: #81D4FA;}");
    connect(ui->isFrog, &QCheckBox::checkStateChanged, this, [=] {
        if (ui->isFrog->isChecked()) ui->isFrog->setText("LeapFrog");
        else ui->isFrog->setText("Not LeapFrog");
    });

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

    int y = windowHeight * 0.05;
    ui->isRandom->move(ButtonSize * width + windowWidth * 0.03, y);

    y += ui->isRandom->height() + windowHeight * 0.015;
    ui->heightLabel->move(ButtonSize * width + windowWidth * 0.03, y);
    ui->heightInput->move(ButtonSize * width + ui->heightLabel->width() + windowWidth * 0.04, y);
    ui->widthLabel->move(ButtonSize * width + ui->heightLabel->width() + ui->heightInput->width() + windowWidth * 0.05, y);
    ui->widthInput->move(ButtonSize * width + ui->heightLabel->width() + ui->heightInput->width() + ui->widthLabel->width() + windowWidth * 0.06, y);

    y += ui->heightLabel->height() + windowHeight * 0.015;
    ui->playerNumberLabel->move(ButtonSize * width + windowWidth * 0.03, y);
    ui->playerNumberInput->move(ButtonSize * width + ui->playerNumberLabel->width() + windowWidth * 0.04, y);

    y += ui->playerNumberLabel->height() + windowHeight * 0.015;
    ui->playerNameInput->setText(playerName);
    ui->playerNameLabel->move(ButtonSize * width + windowWidth * 0.03, y);
    ui->playerNameInput->move(ButtonSize * width + ui->playerNameLabel->width() + windowWidth * 0.04, y);

    y += ui->playerNameLabel->height() + windowHeight * 0.015;
    ui->isVisible->move(ButtonSize * width + windowWidth * 0.03, y);
    ui->isSilent->move(ButtonSize * width + ui->isVisible->width() + windowWidth * 0.04, y);
    ui->isFrog->move(ButtonSize * width + ui->isVisible->width() + ui->isSilent->width() + windowWidth * 0.05, y);
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
