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
    MapInfo *map;
    QPushButton *VisualMap[MaxSize][MaxSize];
    QBrush getBrush(int colorId) const;
    QString getColor(int colorId, const QString &Pic) const;

public slots:
    void setFocusSignal(int x, int y) {
        qDebug() << x << ' ' << y << Qt::endl;
    }

signals:
    void mySignal(int x, int y);
};

#endif // GAMEPAGE_H
