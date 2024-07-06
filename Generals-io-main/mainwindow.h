#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        /*
         * The function paintEvent is to load all the components on the mainwindow.
         * It includes the load of labels, lineedits and buttons
         */
        void paintEvent(QPaintEvent *event);

        /*
         * The function expandTextbox is to expand the width of a lineedit textbox
         * when the number of characters exceeds the maximum capacity.
         */
        void expandTextbox(const QString &text);

        /*
         * The function setNickname is used to show a message box where player should enter his/her nickname.
         */
        void setNickname();

        /*
         * The function setServerAddress is used to show a message box where player should enter his/her server address.
         */
        void setServerAddress();

    private:
        Ui::MainWindow *ui;
        int Nickname_Input_Width = 200;
};
#endif // MAINWINDOW_H
