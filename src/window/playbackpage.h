#ifndef PLAYBACKPAGE_H
#define PLAYBACKPAGE_H

#include <QMainWindow>

namespace Ui {
class PlaybackPage;
}

class PlaybackPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlaybackPage(QWidget *parent = nullptr);
    ~PlaybackPage();

private:
    Ui::PlaybackPage *ui;
    void paintEvent(QPaintEvent *event);
};

#endif // PLAYBACKPAGE_H
