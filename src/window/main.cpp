#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    return a.exec();
}
