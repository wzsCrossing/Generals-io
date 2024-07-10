#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QScopedPointer>
#include <QKeyEvent>
#include "MapInfo.h"
#include "PlayerInfo.h"
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
    void keyPressEvent(QKeyEvent *event);
    void Init(std::shared_ptr<MapInfo> map, QVector<std::shared_ptr<PlayerInfo>> ranklist);
    QString playerName;

private:
    int focus_X;
    int focus_Y;
    int playerNum;
    int width;
    int height;
    Ui::GamePage *ui;
    MapInfo *map;
    QVector<std::shared_ptr<PlayerInfo>> ranklist;
    QPushButton *VisualMap[MaxSize][MaxSize];
    QBrush getBrush(int colorId) const;
    QString getColor(int colorId, const QString &Pic, bool isFocus) const;
signals:
    void moveSignal(int x, int y, Direction dir, bool half);
};

#endif // GAMEPAGE_H
