#ifndef GENERALS_VIEW_MODEL_H
#define GENERALS_VIEW_MODEL_H

#include <QTimer>
#include <QObject>
#include <QString>

#include "etlbase.h"
#include "GameInfo.h"

#include "GeneralsGameModel.h"

#include "StartGameCommand.h"
#include "SetFocusCommand.h"
#include "MoveCommand.h"
#include "SurrenderCommand.h"

#include "GeneralsViewModelSink.h"

class GeneralsViewModel : public QObject,
                          public Proxy_CommandNotification<GeneralsViewModel>,
                          public Proxy_PropertyNotification<GeneralsViewModel> {
Q_OBJECT

public:
    GeneralsViewModel();

    void setModel(const std::shared_ptr<GeneralsGameModel>& model);
    GeneralsGameModel& getModel() throw();

    std::shared_ptr<MapInfo> getMapInfo() throw();
    std::shared_ptr<ICommandBase> getStartGameCommand() throw();
    std::shared_ptr<ICommandBase> getSetFocusCommand() throw();
    std::shared_ptr<ICommandBase> getMoveCommand() throw();
    std::shared_ptr<ICommandBase> getSurrenderCommand() throw();
    bool startGame(const QString &nickname);
    bool setFocus(int x, int y);
    bool move(int x, int y, Direction dir, bool half);
    bool surrender();

signals:
    void mapChanged();

private slots:
    void updateGame();

private:
    QTimer *gameTimer;

    std::shared_ptr<GeneralsGameModel> m_GeneralsModel;

    std::shared_ptr<StartGameCommand> m_cmdStartGame;
    std::shared_ptr<SetFocusCommand> m_cmdSetFocus;
    std::shared_ptr<MoveCommand> m_cmdMove;
    std::shared_ptr<SurrenderCommand> m_cmdSurrender;

    std::shared_ptr<GeneralsViewModelSink> m_sink;
};

#endif // GENERALS_VIEW_MODEL_H