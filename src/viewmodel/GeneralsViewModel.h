#ifndef GENERALS_VIEW_MODEL_H
#define GENERALS_VIEW_MODEL_H

#include "etlbase.h"

#include "GeneralsDataModel.h"

#include "PlayerConnectCommand.h"
#include "PlayerDisconnectCommand.h"
#include "PlayerReadyCommand.h"
#include "ChatCommand.h"
#include "MoveCommand.h"
#include "SurrenderCommand.h"

#include "GeneralsViewModelSink.h"

class GeneralsViewModel : public Proxy_CommandNotification<GeneralsViewModel>,
                          public Proxy_PropertyNotification<GeneralsViewModel> {
public:
    GeneralsViewModel();

    void setModel(const std::shared_ptr<GeneralsDataModel>& model);
    GeneralsDataModel& getModel() throw();

    std::shared_ptr<ICommandBase> getPlayerConnectCommand() throw();
    std::shared_ptr<ICommandBase> getPlayerDisconnectCommand() throw();
    std::shared_ptr<ICommandBase> getPlayerReadyCommand() throw();
    std::shared_ptr<ICommandBase> getChatCommand() throw();
    std::shared_ptr<ICommandBase> getMoveCommand() throw();
    std::shared_ptr<ICommandBase> getSurrenderCommand() throw();
    bool playerConnect(int player_id);
    bool playerDisconnect(int player_id);
    bool playerReady(int player_id);
    bool chat(int player_id, const std::string &msg);
    bool move(int player_id, int x, int y, int dx, int dy);
    bool surrender(int player_id);

private:
    std::shared_ptr<GeneralsDataModel> m_GeneralsModel;
};

#endif // GENERALS_VIEW_MODEL_H