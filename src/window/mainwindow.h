#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
    explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;
        int Nickname_Input_Width = 200;
        /**
         * @brief The function paintEvent is to load all the components on the mainwindow.
         *        It includes the load of labels, lineedits and buttons
         * @param not important
         */
        void paintEvent(QPaintEvent *event);

        /**
         * @brief The function expandTextbox is to expand the width of a lineedit textbox
         * when the number of characters exceeds the maximum capacity.
         * @param text: The text string in the current box.
         */
        void expandTextbox(const QString &text);

    signals:
        void sendNickname(const QString &nickname);
        void goToMapPage();
};
#endif // MAINWINDOW_H
