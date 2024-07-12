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
    int width = MaxSize;
    int height = MaxSize;
    QPushButton *VisualMap[MaxSize][MaxSize];
    std::shared_ptr<MapInfo> map;
    int gameMode;
    QBrush getBrush(int colorId) const;
    QString getColor(int colorId, const QString &Pic) const;

    void paintEvent(QPaintEvent *event);
    void drawVisualMap(int i, int j);

signals:
    void backToMain();
    void startGameRandom(int playerNum, GameMode mode);

public slots:
    void changeMap();
};

#endif // MAPPAGE_H
