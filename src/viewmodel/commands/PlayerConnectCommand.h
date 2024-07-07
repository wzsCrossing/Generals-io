#ifndef PLAYER_CONNECT_COMMAND_H
#define PLAYER_CONNECT_COMMAND_H

#include "etlbase.h"

class GeneralsViewModel;

class PlayerConnectCommand : public ICommandBase {
public:
    PlayerConnectCommand(GeneralsViewModel *p) throw();
    virtual void SetParameter(const std::any &param) override;
    virtual void Exec() override;

private:
    GeneralsViewModel *m_pVM;
    int m_player_id;
};

#endif // PLAYER_CONNECT_COMMAND_H