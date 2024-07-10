#include "GeneralsApp.h"

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

    GeneralsApp generalsApp;
    generalsApp.show();

    return a.exec();
}
