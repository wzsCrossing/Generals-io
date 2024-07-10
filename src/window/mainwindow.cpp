#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QDebug>
#include <QFont>
#include <QFontMetrics>
#include <QMessageBox>
#include <QInputDialog>
#include <QScopedPointer>

MainWindow::MainWindow(QWidget *parent, QSharedPointer<GeneralsViewModel> ViewModel)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mappage(new MapPage(parent, ViewModel))
    , ViewModel(ViewModel)
{
    ui->setupUi(this);
    this->setWindowTitle("Generals.io");
    this->resize(960, 840);
    connect(ui->Input_Nickname, &QLineEdit::textChanged, this, &MainWindow::expandTextbox);
    connect(ui->Input_Nickname, &QLineEdit::returnPressed, this, [=] {
                                                                        this->hide();
                                                                        mappage->show();
                                                                        mappage->playerName = ui->Input_Nickname->text();
                                                                        emit sendNickname(ui->Input_Nickname->text());
                                                                     });
    connect(ui->Ready_Button, &QPushButton::clicked, this, [=]  {
                                                                    this->hide();
                                                                    mappage->show();
                                                                    mappage->playerName = ui->Input_Nickname->text();
                                                                    emit sendNickname(ui->Input_Nickname->text());
                                                                });
    connect(this, SIGNAL(sendNickname(QString)), ViewModel.data(), SLOT(setPlayerName(QString)));
    connect(mappage, &MapPage::backToMain, this, [=] {this->show();
                                                      mappage->hide();
                                                     });
    this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mappage;
}

void MainWindow::expandTextbox(const QString &text) {
    static bool flag = false;
    if (text.size() > 50) {
        flag = true;
        QMessageBox::information(this, "Warning", "Your name must be no more than 50 characters!");
        ui->Input_Nickname->setText(text.left(50));
        return;
    } //The nickname has the maximum number of characters of 50
    int TextSize = 16 * text.size();
    Nickname_Input_Width = (TextSize > 200) ? TextSize : 200;
    ui->Input_Nickname->resize(Nickname_Input_Width, 40);
}

void MainWindow::paintEvent(QPaintEvent *event) {

    /*
     * Load the crown picture
     */
    QPainter painter(this);
    QPixmap General_Blue(":/General-Blue.png");
    int Window_Height = this->size().rheight();
    int Window_Width = this->size().rwidth();
    int Pic_Height = Window_Height * 0.2;
    int Pic_Width = Window_Width * 0.2;
    if (Pic_Height > Pic_Width) Pic_Height = Pic_Width;
        else Pic_Width = Pic_Height;
    int Pix_X = (Window_Width - Pic_Width) / 2;
    int Pix_Y = Window_Height * 0.33 - Pic_Height * 0.5;
    painter.drawPixmap(Pix_X, Pix_Y, Pic_Height, Pic_Width, General_Blue);

    /*
     * Load the Title Label
     */
    QFont font("Consolas", 70);
    font.setBold(true);

    int Title_Y = Window_Height * 0.06;
    ui->Title->setGeometry(0, Title_Y, Window_Width, 80);
    ui->Title->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->Title->setFont(font);
    ui->Title->setStyleSheet("color: #81D4FA");

    /*
     * Load the Nickname Label
     */

    int Nickname_Label_Y = Pix_Y + Pic_Height + Window_Height * 0.03;
    ui->Nickname_Label->setGeometry(0, Nickname_Label_Y, Window_Width, 40);
    font.setPointSize(17);
    ui->Nickname_Label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->Nickname_Label->setFont(font);
    ui->Nickname_Label->setStyleSheet("color: #81D4FA");

    /*
     * Load the Nickname input textblock
     */
    int Nickname_Input_X = (Window_Width - ui->Input_Nickname->width()) / 2;
    int Nickname_Input_Y = Nickname_Label_Y + Window_Height * 0.05;
    ui->Input_Nickname->setGeometry(Nickname_Input_X, Nickname_Input_Y, Nickname_Input_Width, 40);
    font.setPointSize(17);
    ui->Input_Nickname->setFont(font);
    ui->Input_Nickname->setPlaceholderText("Anonymous");
    ui->Input_Nickname->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    /*
     * Load the Address Label
     */

    int Address_Label_Y = Nickname_Input_Y + Window_Height * 0.07;
    ui->Address_Label->setGeometry(0, Address_Label_Y, Window_Width, 40);
    font.setPointSize(17);
    ui->Address_Label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->Address_Label->setFont(font);
    ui->Address_Label->setStyleSheet("color: #81D4FA");

    /*
     * Load the Address input textblock
     */
    int Address_Input_Width = 200;
    int Address_Input_X = (Window_Width - ui->Input_Address->width()) / 2;
    int Address_Input_Y = Address_Label_Y + Window_Height * 0.05;
    ui->Input_Address->setGeometry(Address_Input_X, Address_Input_Y, Address_Input_Width, 40);
    font.setPointSize(17);
    ui->Input_Address->setFont(font);
    ui->Input_Address->setPlaceholderText("Coming Soon!");
    ui->Input_Address->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->Input_Address->setReadOnly(true);

    /*
     * Load the Connect Button
     */
    int Connect_Button_Width = 160;
    int Connect_Button_Height = 40;
    int Connect_Button_X = Window_Width * 0.3 - Connect_Button_Width / 2;
    int Connect_Button_Y = Address_Input_Y + Window_Height * 0.2;
    ui->Connect_Button->setGeometry(Connect_Button_X, Connect_Button_Y, Connect_Button_Width, Connect_Button_Height);
    ui->Connect_Button->setFont(font);
    ui->Connect_Button->setStyleSheet("QPushButton:hover{background:#81D4FA;}"\
                                      "QPushButton:pressed{background:blue;}"\
                                      "QPushButton{background: #029FFF; border-radius: 8px;}");

    /*
     * Load the Ready Button
     */
    int Ready_Button_Width = 160;
    int Ready_Button_Height = 40;
    int Ready_Button_X = Window_Width * 0.7 - Ready_Button_Width / 2;
    int Ready_Button_Y = Connect_Button_Y;
    ui->Ready_Button->setGeometry(Ready_Button_X, Ready_Button_Y, Ready_Button_Width, Ready_Button_Height);
    ui->Ready_Button->setFont(font);
    ui->Ready_Button->setStyleSheet("QPushButton:hover{background:#81D4FA;}"\
                                    "QPushButton:pressed{background:blue;}"\
                                    "QPushButton{background: #029FFF; border-radius: 8px;}");

}
