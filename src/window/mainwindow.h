#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QStackedWidget>
#include "mappage.h"

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
        MapPage *mappage = nullptr;
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
        void startGame();
        void gameStarted(std::shared_ptr<MapInfo> map, QVector<std::shared_ptr<PlayerInfo>> ranklist);
    public slots:
        void initFinished(std::shared_ptr<MapInfo> map, QVector<std::shared_ptr<PlayerInfo>> ranklist);
};
#endif // MAINWINDOW_H
