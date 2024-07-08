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
    ~MapPage();
    void goToGamePage();

private:
    Ui::MapPage *ui;
    GamePage *gamepage;
};

#endif // MAPPAGE_H
