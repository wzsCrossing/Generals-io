#ifndef MAPPAGE_H
#define MAPPAGE_H

#include <QMainWindow>
#include <QPushButton>
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

private:
    Ui::MapPage *ui;
    int width;
    int height;
    //QPushButton *VisualMap[MaxSize][MaxSize];

    void paintEvent(QPaintEvent *event);

public slots:
    void show();

signals:
    void backToMain();
};

#endif // MAPPAGE_H
