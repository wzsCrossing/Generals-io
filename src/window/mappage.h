#ifndef MAPPAGE_H
#define MAPPAGE_H

#include <QMainWindow>
#include "gamepage.h"
#define MaxSize 25

namespace Ui {
class MapPage;
}

class MapPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapPage(QWidget *parent = nullptr);
    ~MapPage();
    QString playerName;
    GamePage *getGamePage();

private:
    Ui::MapPage *ui;
    GamePage *gamepage;
    int width;
    int height;
    QPushButton *VisualMap[MaxSize][MaxSize];

    void paintEvent(QPaintEvent *event);

signals:
    void backToMain();
    void startGame();
};

#endif // MAPPAGE_H
