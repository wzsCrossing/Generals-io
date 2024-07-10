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
public slots:
    void gameStarted(std::shared_ptr<MapInfo> map, QVector<std::shared_ptr<PlayerInfo>> ranklist);
};

#endif // MAPPAGE_H
