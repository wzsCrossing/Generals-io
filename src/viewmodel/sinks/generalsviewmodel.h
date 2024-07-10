#ifndef GENERALSVIEWMODEL_H
#define GENERALSVIEWMODEL_H

#include <QObject>
#include <QDebug>
#include <GameInfo.h>
#include <QSharedPointer>

class GeneralsViewModel : public QObject
{
    Q_OBJECT
public:
    explicit GeneralsViewModel(QObject *parent = nullptr);

signals:

public slots:
    void setPlayerName(const QString &nickname) {
        qDebug() << nickname << Qt::endl;
    }
    void move(int x, int y, Direction dir, bool half) {
        qDebug() << x << ' ' << y << ' ';
        switch (dir) {
            case Direction::UP :
                qDebug() << "Up" << ' ';
                break;
            case Direction::DOWN :
                qDebug() << "Down" << ' ';
                break;
            case Direction::LEFT :
                qDebug() << "Left" << ' ';
                break;
            case Direction::RIGHT :
                qDebug() << "Right" << ' ';
                break;
        }
        if (half) qDebug() << "half\n";
            else qDebug() << "whole\n";
    }
};

#endif // GENERALSVIEWMODEL_H
