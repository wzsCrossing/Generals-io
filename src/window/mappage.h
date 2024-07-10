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
    explicit MapPage(QWidget *parent = nullptr, QSharedPointer<GeneralsViewModel> ViewModel = nullptr);
    ~MapPage();
    QString playerName;

private:
    Ui::MapPage *ui;
    GamePage *gamepage;
    int width;
    int height;
    QPushButton *VisualMap[MaxSize][MaxSize];
    QSharedPointer<GeneralsViewModel> ViewModel;

    void paintEvent(QPaintEvent *event);
    void setViewModel();


signals:
    void backToMain();
};

#endif // MAPPAGE_H
