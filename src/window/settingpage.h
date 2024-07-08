#ifndef SETTINGPAGE_H
#define SETTINGPAGE_H

#include <QMainWindow>

namespace Ui {
class SettingPage;
}

class SettingPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingPage(QWidget *parent = nullptr);
    ~SettingPage();

private:
    Ui::SettingPage *ui;
};

#endif // SETTINGPAGE_H
