#include "playbackpage.h"
#include "ui_playbackpage.h"
#include <QFont>

PlaybackPage::PlaybackPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlaybackPage)
{
    ui->setupUi(this);
    this->setWindowTitle("Generals.io");
    this->resize(1280, 840);
    QPalette pal;
    pal.setColor(QPalette::Window, QColor(QColor::fromRgb(36, 36, 36)));
    this->setPalette(pal);
    QFont font("Consolas", 17);
    ui->lastRound->setFont(font);
    ui->lastRound->setStyleSheet("QPushButton:hover{background:#81D4FA;}"\
                                 "QPushButton:pressed{background:blue;}"\
                                 "QPushButton{background: #029FFF; border-radius: 8px;}");
    connect(ui->lastRound, &QPushButton::clicked, this, [=] {
    });

    ui->nextRound->setFont(font);
    ui->nextRound->setStyleSheet("QPushButton:hover{background:#81D4FA;}"\
                                 "QPushButton:pressed{background:blue;}"\
                                 "QPushButton{background: #029FFF; border-radius: 8px;}");
    connect(ui->nextRound, &QPushButton::clicked, this, [=] {
    });

    ui->autoPlay->setFont(font);
    ui->autoPlay->setStyleSheet("QPushButton:hover{background:#81D4FA;}"\
                                "QPushButton:pressed{background:blue;}"\
                                "QPushButton{background: #029FFF; border-radius: 8px;}");
    connect(ui->autoPlay, &QPushButton::clicked, this, [=] {
    });
}

PlaybackPage::~PlaybackPage()
{
    delete ui;
}


void PlaybackPage::paintEvent(QPaintEvent *event) {
    int width = 16, height = 16;
    int WindowWidth = this->size().rwidth(), WindowHeight = this->size().rheight();
    int max = (width > height) ? width : height;
    int ButtonSize = WindowHeight / max / 1.2;
    QFont font("Consolas", ButtonSize / 2.5);

    /*
     * To construct surrender button
     */

    font.setBold(true);
    int lastRound_Button_Width = 140;
    int lastRound_Button_Height = 40;
    int lastRound_Button_X = WindowWidth / 6 - lastRound_Button_Width / 2;
    int lastRound_Button_Y = height * ButtonSize + ButtonSize / 2;
    ui->lastRound->setGeometry(lastRound_Button_X, lastRound_Button_Y, lastRound_Button_Width, lastRound_Button_Height);

    /*
     * To construct back to map button
     */

    font.setBold(true);
    int nextRound_Button_Width = 140;
    int nextRound_Button_Height = 40;
    int nextRound_Button_X = WindowWidth / 6 * 3 - nextRound_Button_Width / 2;
    int nextRound_Button_Y = height * ButtonSize + ButtonSize / 2;
    ui->nextRound->setGeometry(nextRound_Button_X, nextRound_Button_Y, nextRound_Button_Width, nextRound_Button_Height);

    /*
     * To construct playback button
     */

    font.setBold(true);
    int autoPlay_Button_Width = 140;
    int autoPlay_Button_Height = 40;
    int autoPlay_Button_X = WindowWidth / 6 * 5 - autoPlay_Button_Width / 2;
    int autoPlay_Button_Y = height * ButtonSize + ButtonSize / 2;
    ui->autoPlay->setGeometry(autoPlay_Button_X, autoPlay_Button_Y, autoPlay_Button_Width, autoPlay_Button_Height);
}
