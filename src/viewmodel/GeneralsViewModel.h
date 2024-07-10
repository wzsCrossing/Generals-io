#ifndef GENERALS_VIEW_MODEL_H
#define GENERALS_VIEW_MODEL_H

#include <QTimer>
#include <QObject>
#include <QString>
#include <QVector>
#include "PlayerInfo.h"
#include "MapInfo.h"
#include "GeneralsGameModel.h"

class GeneralsViewModel : public QObject {
Q_OBJECT
public:
    GeneralsViewModel();

    void setModel(const std::shared_ptr<GeneralsGameModel>& model);
    GeneralsGameModel& getModel() throw();

    std::shared_ptr<MapInfo> getMapInfo() throw();
    QString getPlayerName();
    QVector<std::shared_ptr<PlayerInfo>> getRankList() throw();

public slots:
    void setPlayerName(const QString &nickname);
    void startGame();
    void setFocus(int x, int y);
    void move(int x, int y, Direction dir, bool half);
    void surrender();

signals:
    void mapChanged(std::shared_ptr<MapInfo> map, QVector<std::shared_ptr<PlayerInfo>> ranklist, int round);
    void successfulMove(Direction dir);
    void playerDie(const QString &playerName);

private slots:
    void updateGame();

private:
    QTimer *gameTimer;

    std::shared_ptr<GeneralsGameModel> m_GeneralsModel;
};

#endif // GENERALS_VIEW_MODEL_H
