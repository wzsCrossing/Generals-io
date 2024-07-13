#ifndef PLAYBACKPAGE_H
#define PLAYBACKPAGE_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include "MapInfo.h"
#include "PlayerInfo.h"
#define MaxSize 25

namespace Ui {
class PlaybackPage;
}

class PlaybackPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlaybackPage(QWidget *parent = nullptr);
    void setMaxRound(int round);
    void Init();
    ~PlaybackPage();

private:
    int round = 0;
    int maxRound;
    Ui::PlaybackPage *ui;
    QTimer *gameTimer;
    QPushButton *VisualMap[MaxSize][MaxSize];
    void drawVisualMap(int i, int j);
    QString getColor(int colorId, const QString &Pic) const;

public slots:
    void changeMapInfo(std::shared_ptr<MapInfo> map);

signals:
    void roundSignal(int round);
};

#endif // PLAYBACKPAGE_H
