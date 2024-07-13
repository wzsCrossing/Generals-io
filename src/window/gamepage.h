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
    void setMap(std::shared_ptr<MapInfo> map) {this->map = map;}
    void setRanklist(std::shared_ptr<QVector<std::shared_ptr<PlayerInfo>>> ranklist) {this->ranklist = ranklist;}
    void setRound(int round) {this->round = round;};
    void setMode(bool isVisible, bool isSilent);
    void Init();
    QTimer* getTimer();
    QString playerName;

private:
    QString getDirection(int dir);
    int focus_X, focus_Y;
    int playerNum;
    int round;
    int width, height;
    bool half = false;
    bool isVisible;
    bool isSilent;
    Ui::GamePage *ui;
    std::shared_ptr<MapInfo> map;
    std::shared_ptr<QVector<std::shared_ptr<PlayerInfo>>> ranklist;
    QPushButton *VisualMap[MaxSize][MaxSize];
    QTimer *gameTimer;
    QBrush getBrush(int colorId) const;
    QString getColor(int colorId, const QString &Pic, bool isFocus) const;
    void paintFocus(int origin_x, int origin_y, int new_x, int new_y);
    void drawVisualMap(int i, int j, bool focus);

signals:
    void moveSignal(int x, int y, Direction dir, bool half);
    void surrender();
    void gameEnded();
    void undo();
    void clearMove();

public slots:
    void changeMapInfo();
    void moveFocus(Direction dir);
};

#endif // GAMEPAGE_H
