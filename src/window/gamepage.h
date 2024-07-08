#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QMainWindow>
#include <MapInfo.h>
#include <QPushButton>
#include <QLabel>
#include <QScopedPointer>
#define MaxSize 16

namespace Ui {
class GamePage;
}

class GamePage : public QMainWindow
{
    Q_OBJECT

public:
    explicit GamePage(QWidget *parent = nullptr);
    ~GamePage();
    void paintEvent(QPaintEvent *event);

private:
    Ui::GamePage *ui;
    Cell map[MaxSize][MaxSize];
    QPushButton *VisualMap[MaxSize][MaxSize];
    QLabel *ArmyNumber[MaxSize][MaxSize];
    QString getColor(int colorId) const;
};

#endif // GAMEPAGE_H
