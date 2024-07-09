#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QMainWindow>
#include "MapInfo.h"
#include <QPushButton>
#include <QLabel>
#include <QScopedPointer>
#define MaxSize 25

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
    //Cell map[MaxSize][MaxSize];
    MapInfo *map;
    QPushButton *VisualMap[MaxSize][MaxSize];
    QLabel *ArmyNumber[MaxSize][MaxSize];
    QString getColor(int colorId) const;
    QBrush getBrush(int colorId) const;
    void setFocusSignal(int x, int y);

signals:
    void focusSignal(int x, int y);
};

#endif // GAMEPAGE_H
