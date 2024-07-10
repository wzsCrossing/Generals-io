#ifndef MAPPAGE_H
#define MAPPAGE_H

#include <QMainWindow>
#include "gamepage.h"

namespace Ui {
class MapPage;
}

class MapPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapPage(QWidget *parent = nullptr);
    QString playerName;
    ~MapPage();

private:
    Ui::MapPage *ui;
    GamePage *gamepage;
    void paintEvent(QPaintEvent *event);

signals:
    void backToMain();
};

#endif // MAPPAGE_H
