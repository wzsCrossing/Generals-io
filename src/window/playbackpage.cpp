#include "playbackpage.h"
#include "ui_playbackpage.h"
#include <QFont>

PlaybackPage::PlaybackPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlaybackPage)
    , gameTimer(new QTimer(this))
{
    ui->setupUi(this);
    this->setWindowTitle("Generals.io");
    this->resize(1280, 840);
    QPalette pal;
    pal.setColor(QPalette::Window, QColor(QColor::fromRgb(36, 36, 36)));
    this->setPalette(pal);
    QFont font("Consolas", 17);
    font.setBold(true);
    ui->lastRound->setFont(font);
    ui->lastRound->setStyleSheet("QPushButton:hover{background:#81D4FA;}"\
                                 "QPushButton:pressed{background:blue;}"\
                                 "QPushButton{background: #029FFF; border-radius: 8px;}");
    ui->lastRound->resize(140, 40);
    ui->lastRound->setDisabled(true);
    connect(ui->lastRound, &QPushButton::clicked, this, [=] {
        round--;
        ui->nextRound->setDisabled(false);
        if (round == 0) ui->lastRound->setDisabled(true);
        emit roundSignal(round);
    });

    ui->nextRound->setFont(font);
    ui->nextRound->setStyleSheet("QPushButton:hover{background:#81D4FA;}"\
                                 "QPushButton:pressed{background:blue;}"\
                                 "QPushButton{background: #029FFF; border-radius: 8px;}");
    ui->nextRound->resize(140, 40);
    connect(ui->nextRound, &QPushButton::clicked, this, [=] {
        round++;
        ui->lastRound->setDisabled(false);
        if (round == maxRound) ui->nextRound->setDisabled(true);
        emit roundSignal(round);
    });

    ui->autoPlay->setFont(font);
    ui->autoPlay->setStyleSheet("QPushButton:hover{background:#81D4FA;}"\
                                "QPushButton:pressed{background:blue;}"\
                                "QPushButton{background: #029FFF; border-radius: 8px;}");
    ui->autoPlay->resize(140, 40);
    connect(ui->autoPlay, &QPushButton::clicked, this, [=] {
        if (ui->autoPlay->text() == "Auto Play") {
            ui->autoPlay->setText("Stop Play");
            ui->lastRound->setDisabled((round == 0));
            ui->nextRound->setDisabled((round == maxRound));
            ui->speedButton->setDisabled(false);
            ui->restart->setDisabled(false);
            gameTimer->stop();
        } else {
            ui->autoPlay->setText("Auto Play");
            if (ui->speedButton->text() == "×0.5") gameTimer->start(1000);
                else if (ui->speedButton->text() == "×1") gameTimer->start(500);
                    else if (ui->speedButton->text() == "×2") gameTimer->start(250);
                        else gameTimer->start(125);
            ui->lastRound->setDisabled(true);
            ui->nextRound->setDisabled(true);
            ui->speedButton->setDisabled(true);
            ui->restart->setDisabled(true);
        }
    });
    connect(gameTimer, &QTimer::timeout, this, [=]{
        if (round < maxRound) {
            ++round;
            emit roundSignal(round);
        } else {
            gameTimer->stop();
            ui->autoPlay->setText("Stop Play");
            ui->lastRound->setDisabled(false);
            ui->nextRound->setDisabled(true);
            ui->speedButton->setDisabled(false);
            ui->restart->setDisabled(false);
        }
    });

    ui->restart->setFont(font);
    ui->restart->setStyleSheet("QPushButton:hover{background:#81D4FA;}"\
                                 "QPushButton:pressed{background:blue;}"\
                                 "QPushButton{background: #029FFF; border-radius: 8px;}");
    ui->restart->resize(140, 40);
    connect(ui->restart, &QPushButton::clicked, this, [=] {
        round = 0;
        ui->lastRound->setDisabled(true);
        ui->nextRound->setDisabled(false);
        ui->autoPlay->setDisabled(false);
        emit roundSignal(0);
    });
    ui->restart->setText("Restart");

    for (int i = 0; i < MaxSize; i++)
        for (int j = 0; j < MaxSize; j++) {
            VisualMap[i][j] = new QPushButton(this);
            VisualMap[i][j]->hide();
        }

    ui->currentRound->setFont(font);
    ui->currentRound->setStyleSheet("color: #81D4FA");
    ui->currentRound->resize(320, 40);

    ui->maxRound->setFont(font);
    ui->maxRound->setStyleSheet("color: #81D4FA");
    ui->maxRound->resize(320, 40);

    ui->speedLabel->setFont(font);
    ui->speedLabel->setStyleSheet("color: #81D4FA");
    ui->speedLabel->resize(80, 40);

    ui->speedButton->setFont(font);
    ui->speedButton->setStyleSheet("color: #81D4FA");
    ui->speedButton->resize(80, 40);
    ui->speedButton->setText("×1");
    connect(ui->speedButton, &QPushButton::clicked, this, [=] {
        if (ui->speedButton->text() == "×1") ui->speedButton->setText("×2");
            else if (ui->speedButton->text() == "×2") ui->speedButton->setText("×4");
                else if (ui->speedButton->text() == "×4") ui->speedButton->setText("×0.5");
                    else ui->speedButton->setText("×1");
    });
}

void PlaybackPage::Init() {
    for (int i = 0; i < MaxSize; i++)
        for (int j = 0; j < MaxSize; j++) {
            VisualMap[i][j]->hide();
        }
    emit roundSignal(0);
}

PlaybackPage::~PlaybackPage()
{
    delete ui;
    for (int i = 0; i <MaxSize; i++)
        for (int j = 0; j <MaxSize; j++)
            delete VisualMap[i][j];
}

void PlaybackPage::setMaxRound(int round) {
    maxRound = round;
}

QString PlaybackPage::getColor(int colorId, const QString &Pic) const{
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

void PlaybackPage::changeMapInfo(std::shared_ptr<MapInfo> map) {
    int width = map->getWidth(), height = map->getHeight();
    int WindowWidth = this->size().rwidth(), WindowHeight = this->size().rheight();
    int max = (width > height) ? width : height;
    int ButtonSize = WindowHeight / max / 1.2;
    QFont font("Consolas", ButtonSize / 2.5);

    /*
     * To construct last round button
     */

    font.setBold(true);
    int lastRound_Button_X = WindowWidth / 8 - 70;
    int lastRound_Button_Y = height * ButtonSize + ButtonSize / 2;
    ui->lastRound->setGeometry(lastRound_Button_X, lastRound_Button_Y, 140, 40);

    /*
     * To construct next round button
     */

    int nextRound_Button_X = WindowWidth / 8 * 3 - 70;
    int nextRound_Button_Y = height * ButtonSize + ButtonSize / 2;
    ui->nextRound->setGeometry(nextRound_Button_X, nextRound_Button_Y, 140, 49);

    /*
     * To construct auto button
     */

    int autoPlay_Button_X = WindowWidth / 8 * 5 - 70;
    int autoPlay_Button_Y = height * ButtonSize + ButtonSize / 2;
    ui->autoPlay->setGeometry(autoPlay_Button_X, autoPlay_Button_Y, 140, 40);

    /*
     * To construct restart button
     */

    int restart_Button_X = WindowWidth / 8 * 7 - 70;
    int restart_Button_Y = height * ButtonSize + ButtonSize / 2;
    ui->restart->setGeometry(restart_Button_X, restart_Button_Y, 140, 40);

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            VisualMap[i][j]->show();
            VisualMap[i][j]->setGeometry(j * ButtonSize, i * ButtonSize, ButtonSize, ButtonSize);
            VisualMap[i][j]->setFont(font);
            switch (map->getCell(i, j)->getType()) {
            case CellType::BLANK :
                VisualMap[i][j]->setIcon(QIcon());
                VisualMap[i][j]->setStyleSheet(getColor(map->getCell(i, j)->getArmy() > 0 ? map->getCell(i, j)->getOwner() : 8, ""));
                VisualMap[i][j]->setText((map->getCell(i, j)->getArmy() > 0 ? QString::number(map->getCell(i, j)->getArmy()) : ""));
                break;
            case CellType::CAPITAL :
                VisualMap[i][j]->setIcon(QIcon());
                VisualMap[i][j]->setStyleSheet(getColor(map->getCell(i, j)->getOwner(), ":/General.png"));
                VisualMap[i][j]->setText((QString::number(map->getCell(i, j)->getArmy())));
                break;
            case CellType::CITY :
                VisualMap[i][j]->setIcon(QIcon());
                VisualMap[i][j]->setStyleSheet(getColor(map->getCell(i, j)->getOwner(), ":/City.png"));
                VisualMap[i][j]->setText((QString::number(map->getCell(i, j)->getArmy())));
                break;
            case CellType::MOUNTAIN :
                VisualMap[i][j]->setIcon(QIcon(":/Mountain.png"));
                VisualMap[i][j]->setIconSize(QSize(ButtonSize, ButtonSize));
                VisualMap[i][j]->setStyleSheet("QPushButton {background: grey; border-radius: 0px; border: 1px solid black;}");
                VisualMap[i][j]->setText("");
                break;
            }
        }

    ui->currentRound->move(ButtonSize * width + ButtonSize / 2, WindowHeight * 0.1);
    ui->currentRound->setText("Current Round : " + QString::number(round));
    ui->maxRound->move(ButtonSize * width + ButtonSize / 2, WindowHeight * 0.2);
    ui->maxRound->setText("Max Round : " + QString::number(maxRound));
    ui->speedLabel->move(ButtonSize * width + ButtonSize / 2, WindowHeight * 0.3);
    ui->speedLabel->setText("speed : ");
    ui->speedButton->move(ButtonSize * width + ButtonSize + ui->speedLabel->width(), WindowHeight * 0.3);
}
