#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QMainWindow>
#include "generalsviewmodel.h"
#include <QPushButton>
#include <QLabel>
#include <QScopedPointer>
#include <QKeyEvent>
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
    int focus_X;
    int focus_Y;

private:
    Ui::GamePage *ui;
    MapInfo *map;
    QPushButton *VisualMap[MaxSize][MaxSize];
    QBrush getBrush(int colorId) const;
    QString getColor(int colorId, const QString &Pic, bool isFocus) const;
    GeneralsViewModel *commands;

public slots:
    void setFocusSignal(int x, int y);

signals:
    void focusSignal(int x, int y);
    void moveSignal(int x, int y, Direction dir, bool half);
};

#endif // GAMEPAGE_H
