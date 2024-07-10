#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QVBoxLayout>
#include <generalsviewmodel.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSharedPointer<GeneralsViewModel> ViewModel(new GeneralsViewModel);
    MainWindow w(nullptr, ViewModel);
    return a.exec();
}
