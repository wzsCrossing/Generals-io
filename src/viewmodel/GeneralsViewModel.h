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
    std::shared_ptr<GeneralsGameModel> getModel() throw();

    std::shared_ptr<MapInfo> getMapInfo() throw();
    QString getPlayerName();
    std::shared_ptr<QVector<std::shared_ptr<PlayerInfo>>> getRankList() throw();

public slots:
    void setPlayerName(const QString &nickname);
    void startGame();
    void setFocus(int x, int y);
    void move(int x, int y, Direction dir, bool half);
    void surrender();
    void updateGame();

signals:
    void mapChanged();
    void successfulMove(Direction dir);
    void playerDie(const QString &playerName);

private:
    std::shared_ptr<GeneralsGameModel> m_GeneralsModel;
};

#endif // GENERALS_VIEW_MODEL_H
