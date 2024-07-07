#ifndef PLAYER_DISCONNECT_COMMAND_H
#define PLAYER_DISCONNECT_COMMAND_H

#include "etlbase.h"

class GeneralsViewModel;

class PlayerDisconnectCommand : public ICommandBase {
public:
    PlayerDisconnectCommand(GeneralsViewModel *p) throw();
    virtual void SetParameter(const std::any &param) override;
    virtual void Exec() override;

private:
    GeneralsViewModel *m_pVM;
    int m_player_id;
};

#endif // PLAYER_DISCONNECT_COMMAND_H