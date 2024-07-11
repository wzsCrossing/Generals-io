#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QScopedPointer>
#include <QKeyEvent>
#include <QTimer>
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
    QTimer* getTimer();
    QString playerName;

private:
    int focus_X, focus_Y;
    int playerNum;
    int round;
    int width, height;
    bool half = false;
    Ui::GamePage *ui;
    MapInfo *map;
    QVector<std::shared_ptr<PlayerInfo>> ranklist;
    QPushButton *VisualMap[MaxSize][MaxSize];
    QTimer *gameTimer;
    QBrush getBrush(int colorId) const;
    QString getColor(int colorId, const QString &Pic, bool isFocus) const;

signals:
    void moveSignal(int x, int y, Direction dir, bool half);

public slots:
    void Init(std::shared_ptr<MapInfo> map, QVector<std::shared_ptr<PlayerInfo>> ranklist, int round);
    void moveFocus(Direction dir);
    void playerDie(const QString &playerName);
};

#endif // GAMEPAGE_H
