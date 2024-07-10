#include "settingpage.h"
#include "ui_settingpage.h"

SettingPage::SettingPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SettingPage)
{
    ui->setupUi(this);
    this->setWindowTitle("Generals.io");
}

SettingPage::~SettingPage()
{
    delete ui;
}
